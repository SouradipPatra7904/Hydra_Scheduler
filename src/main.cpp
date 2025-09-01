#include "Scheduler.hpp"
#include "Process.hpp"
#include <iostream>
#include <vector>

static void demoBanner() {
    std::cout << "CPU Scheduler Simulator (Multi-core, I/O, Arrival-aware)\n";
    std::cout << "Algorithms: 1=FCFS  2=SJF  3=Priority  4=Round-Robin\n";
    std::cout << "View: 1=ASCII  2=GUI\n";
}

int main() {
    demoBanner();

    int algoChoice = 4;
    int viewChoice = 1;
    int cores = 2;
    int tq = 2;

    std::cout << "Choose Algorithm [1-4]: ";
    std::cin >> algoChoice;
    std::cout << "Cores (>=1): ";
    std::cin >> cores;
    if (algoChoice == 4) {
        std::cout << "Time Quantum (RR): ";
        std::cin >> tq;
    }
    std::cout << "View [1=ASCII, 2=GUI]: ";
    std::cin >> viewChoice;

    Algorithm algo = Algorithm::RR;
    switch (algoChoice) {
        case 1: algo = Algorithm::FCFS; break;
        case 2: algo = Algorithm::SJF; break;
        case 3: algo = Algorithm::PRIORITY; break;
        case 4: algo = Algorithm::RR; break;
        default: algo = Algorithm::RR; break;
    }

    ViewMode view = (viewChoice == 2) ? ViewMode::GUI : ViewMode::ASCII;

    // Demo workload:
    // - P1: arrival 0, burst 10, priority 2, I/O at cpuPoint=3 for 3 units
    // - P2: arrival 1, burst 5,  priority 1
    // - P3: arrival 2, burst 9,  priority 4, I/O at cpuPoint=4 for 2 units
    // - P4: arrival 6, burst 6,  priority 3
    std::vector<Process> procs = {
        Process(1, 0, 10, 2, {{3,3}}),
        Process(2, 1,  5, 1, {}),
        Process(3, 2,  9, 4, {{4,2}}),
        Process(4, 6,  6, 3, {})
    };

    Scheduler sched(std::move(procs), algo, tq, cores, view);
    sched.run();
    return 0;
}
