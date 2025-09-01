#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "Process.hpp"
#include <vector>
#include <string>
#include <queue>
#include <map>

enum class Algorithm {
    FCFS,
    SJF,
    PRIORITY,
    RR
};

struct GanttEntry {
    int core;
    int startTime;
    int endTime;
    int pid;
};

class Scheduler {
private:
    int numCores;
    int timeQuantum;
    Algorithm algo;
    std::vector<Process> processes;
    std::vector<GanttEntry> gantt;
    int currentTime;

public:
    Scheduler(int cores, Algorithm a, int tq = 2);

    void addProcess(const Process& p);
    void reset();
    void run();

    const std::vector<Process>& getProcesses() const;
    const std::vector<GanttEntry>& getGantt() const;
    std::string getMetrics() const;
    std::string getAsciiGantt() const;
};

#endif
