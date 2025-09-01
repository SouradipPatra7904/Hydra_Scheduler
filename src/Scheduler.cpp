#include "Scheduler.hpp"
#include "sch_algos/Algorithms.hpp"

#include <algorithm>
#include <iostream>
#include <cassert>

#ifdef USE_GUI
#include <SFML/Graphics.hpp>
#endif

Scheduler::Scheduler(std::vector<Process> procs,
                     Algorithm algo,
                     int timeQuantum,
                     int numCores,
                     ViewMode view)
  : processes(std::move(procs)),
    algo(algo),
    tq(timeQuantum),
    cores(numCores),
    view(view),
    coreSlots(numCores),
    chart(numCores)
{
    // Sort by arrival for deterministic admission order
    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b){
                  if (a.arrivalTime != b.arrivalTime) return a.arrivalTime < b.arrivalTime;
                  return a.pid < b.pid;
              });
}

void Scheduler::admitArrivals() {
    for (auto& p : processes) {
        if (p.state == ProcessState::NEW && p.arrivalTime <= time) {
            p.state = ProcessState::READY;
            readyQueue.push_back(&p);
        }
    }
}

void Scheduler::awakenIO() {
    // Move any blocked processes whose unblockTime <= time back to READY
    for (auto it = blocked.begin(); it != blocked.end();) {
        Process* p = *it;
        if (p->unblockTime <= time) {
            p->state = ProcessState::READY;
            readyQueue.push_back(p);
            it = blocked.erase(it);
        } else {
            ++it;
        }
    }
}

int Scheduler::selectIndex() {
    if (readyQueue.empty()) return -1;
    switch (algo) {
    case Algorithm::FCFS:     
        return selectFCFS(readyQueue, rrPtr);
    
    case Algorithm::SJF:      
        return selectSJF(readyQueue, rrPtr);
    
    case Algorithm::PRIORITY: 
        return selectPriority(readyQueue, rrPtr);
    
    case Algorithm::RR:       
        return selectRR(readyQueue, rrPtr);
        
    }
    return -1;
}

void Scheduler::dispatch() {
    // assign READY processes to any idle core
    for (int c = 0; c < cores; ++c) {
        if (coreSlots[c].current) continue; // busy
        int sel = selectIndex();
        if (sel < 0) {
            // mark idle segment if desired (we add as we tick)
            continue;
        }
        Process* p = readyQueue[sel];
        // remove from ready queue
        readyQueue.erase(readyQueue.begin() + sel);

        p->state = ProcessState::RUNNING;
        if (p->firstStartTime < 0) p->firstStartTime = time;

        // determine how much it can run in this dispatch:
        // by default 1 time unit tick; we aggregate to segments by slotStart/End
        coreSlots[c].current = p;
        coreSlots[c].slotStart = time;

        // We'll let executeOneTick() advance by one unit; segments coalesce across ticks
    }
}

void Scheduler::executeOneTick() {
    // For each core, run the assigned process for one time unit (or idle)
    for (int c = 0; c < cores; ++c) {
        Process* p = coreSlots[c].current;

        if (!p) {
            // idle: record idle segment for this tick
            chart.add(c, -1, time, time+1);
            continue;
        }

        // Check if an IO event triggers *now* (i.e., after consuming the next unit)
        bool willBlock = false;
        int blockDuration = 0;

        // consume one unit of CPU
        p->remainingTime -= 1;
        p->cpuConsumed   += 1;

        // After consuming, see if we hit the next IO event boundary
        if (p->ioIndex < (int)p->ioEvents.size()) {
            const IOEvent& ev = p->ioEvents[p->ioIndex];
            if (p->cpuConsumed >= ev.cpuPoint) {
                willBlock = true;
                blockDuration = ev.duration;
                p->ioIndex++;
            }
        }

        // Update segment (we add per-tick to be simple and coalesce on draw)
        chart.add(c, p->pid, time, time+1);

        bool timeSliceExpired = false;
        if (algo == Algorithm::RR) {
            // RR: slice is tq; we store how long this process has been on this core
            if ( ( (time + 1) - coreSlots[c].slotStart ) >= tq ) {
                timeSliceExpired = true;
            }
        }

        // Decide what to do at the end of this tick
        if (p->remainingTime == 0) {
            p->state = ProcessState::COMPLETED;
            p->completionTime = time + 1;
            coreSlots[c].current = nullptr;
        } else if (willBlock) {
            p->state = ProcessState::BLOCKED;
            p->unblockTime = time + 1 + blockDuration;
            blocked.push_back(p);
            coreSlots[c].current = nullptr;
        } else if (timeSliceExpired) {
            // preempt and place back to ready queue
            p->state = ProcessState::READY;
            readyQueue.push_back(p);
            coreSlots[c].current = nullptr;
        } else {
            // keep running in next tick (stay bound to this core)
        }
    }

    // advance global time by one tick
    time += 1;
}

bool Scheduler::allDone() const {
    for (const auto& p : processes) {
        if (p.state != ProcessState::COMPLETED) return false;
    }
    return true;
}

void Scheduler::printMetrics() {
    int n = (int)processes.size();
    int totalTurn = 0;
    int totalWait = 0;
    int totalResp = 0;
    int makespan = 0;
    int totalBurst = 0;

    for (const auto& p : processes) {
        makespan = std::max(makespan, p.completionTime);
        totalBurst += p.burstTime;
    }

    std::cout << "\n=== Metrics ===\n";
    std::cout << "PID  Arr  Burst  Prio  Start  Complete  Turnaround  Waiting  Response\n";
    for (const auto& p : processes) {
        int turnaround = p.completionTime - p.arrivalTime;
        // Waiting = turnaround - CPU burst - IO durations
        int waiting = turnaround - p.burstTime - p.totalIODuration;
        int response = (p.firstStartTime >= 0) ? (p.firstStartTime - p.arrivalTime) : 0;

        totalTurn += turnaround;
        totalWait += waiting;
        totalResp += response;

        std::cout << "P" << p.pid << "   "
                  << p.arrivalTime << "    "
                  << p.burstTime << "     "
                  << p.priority << "     "
                  << (p.firstStartTime < 0 ? -1 : p.firstStartTime) << "      "
                  << p.completionTime << "        "
                  << turnaround << "          "
                  << waiting << "       "
                  << response << "\n";
    }

    double avgTurn = (double)totalTurn / n;
    double avgWait = (double)totalWait / n;
    double avgResp = (double)totalResp / n;
    double cpuUtil = makespan > 0 ? (100.0 * totalBurst / (makespan * cores)) : 0.0;
    double throughput = makespan > 0 ? (double)n / makespan : 0.0;

    std::cout << "Makespan: " << makespan << "\n";
    std::cout << "Avg Turnaround: " << avgTurn << "\n";
    std::cout << "Avg Waiting: "    << avgWait << "\n";
    std::cout << "Avg Response: "   << avgResp << "\n";
    std::cout << "CPU Utilization: " << cpuUtil << "%\n";
    std::cout << "Throughput: "      << throughput << " procs/unit time\n";

    // ASCII chart dump
    chart.displayASCII(makespan, /*timeScale*/1);

#ifdef USE_GUI
    if (view == ViewMode::GUI) {
        int pxPerUnit = 12;
        int rowH = 36;
        int height = 80 + cores * (rowH + 14);
        int width  = std::max(640, 80 + makespan * pxPerUnit);

        sf::RenderWindow window(sf::VideoMode(width, height), "CPU Scheduler - Gantt Chart");
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }
            chart.displayGUI(window, pxPerUnit, rowH);
        }
    }
#endif
}

void Scheduler::run() {
    // main loop
    while (!allDone()) {
        awakenIO();
        admitArrivals();
        dispatch();
        executeOneTick();
    }
    printMetrics();
}
