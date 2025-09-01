#include "Scheduler.hpp"
#include <algorithm>
#include <sstream>
#include <iomanip>

Scheduler::Scheduler(int cores, Algorithm a, int tq)
    : numCores(cores), timeQuantum(tq), algo(a), currentTime(0) {}

void Scheduler::addProcess(const Process& p) {
    processes.push_back(p);
}

void Scheduler::reset() {
    for (auto& p : processes) p.reset();
    gantt.clear();
    currentTime = 0;
}

void Scheduler::run() {
    reset();
    int n = processes.size();
    int finished = 0;
    std::vector<int> coreAvailable(numCores, 0);

    while (finished < n) {
        for (int core = 0; core < numCores; core++) {
            auto it = std::find_if(processes.begin(), processes.end(),
                [&](Process& p) {
                    return !p.completed && p.arrivalTime <= currentTime;
                });

            if (it != processes.end()) {
                int execTime = (algo == Algorithm::RR) ? 
                               std::min(timeQuantum, it->remainingTime) : 
                               it->remainingTime;

                gantt.push_back({core, currentTime, currentTime + execTime, it->pid});
                it->remainingTime -= execTime;
                currentTime += execTime;

                if (it->remainingTime <= 0) {
                    it->completed = true;
                    it->completionTime = currentTime;
                    it->turnaroundTime = it->completionTime - it->arrivalTime;
                    it->waitingTime = it->turnaroundTime - it->burstTime;
                    finished++;
                }
            } else {
                currentTime++;
            }
        }
    }
}

const std::vector<Process>& Scheduler::getProcesses() const { return processes; }
const std::vector<GanttEntry>& Scheduler::getGantt() const { return gantt; }

std::string Scheduler::getMetrics() const {
    std::ostringstream out;
    out << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto& p : processes) {
        out << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime
            << "\t" << p.completionTime << "\t" << p.turnaroundTime
            << "\t" << p.waitingTime << "\n";
    }
    return out.str();
}

std::string Scheduler::getAsciiGantt() const {
    std::ostringstream out;
    for (const auto& e : gantt) {
        out << "[Core " << e.core << " | P" << e.pid
            << " | " << e.startTime << "-" << e.endTime << "] ";
    }
    return out.str();
}
