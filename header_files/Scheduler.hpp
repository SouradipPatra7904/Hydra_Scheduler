#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <vector>
#include <queue>
#include <functional>
#include "Process.hpp"
#include "GanttChart.hpp"

enum class Algorithm { FCFS, SJF, PRIORITY, RR };
enum class ViewMode { ASCII, GUI };

struct CoreSlot {
    // Who is running here during [busyUntilStart, busyUntilEnd)
    Process* current {nullptr};
    int slotStart {0};
    int slotEnd {0}; // exclusive
};

class Scheduler {
public:
    Scheduler(std::vector<Process> procs,
              Algorithm algo,
              int timeQuantum = 2,
              int numCores = 2,
              ViewMode view = ViewMode::ASCII);

    // Runs the full simulation (deterministic, tick-driven)
    void run();

private:
    // state
    std::vector<Process> processes;
    Algorithm algo;
    int tq;
    int cores;
    ViewMode view;

    // scheduling structures
    std::vector<CoreSlot> coreSlots;       // core states
    std::vector<Process*> readyQueue;      // processes READY to run
    std::vector<Process*> blocked;         // BLOCKED processes (I/O)
    int rrPtr = 0;                         // round-robin pointer

    // timeline + metrics
    int time = 0;                          // global wall-clock time
    GanttChart chart;

    // helpers
    void admitArrivals();                  // move NEW->READY when arrivalTime <= time
    void awakenIO();                       // unblock processes whose I/O finished
    void dispatch();                       // assign ready processes to idle cores
    void executeOneTick();                 // run one time unit on busy cores
    bool allDone() const;                  // done?

    // algorithm selection: returns index in readyQueue to schedule next
    int selectIndex();

    // metrics
    void printMetrics();
};

#endif
