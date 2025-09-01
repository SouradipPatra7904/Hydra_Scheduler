#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>
#include <vector>

struct IOEvent {
    int startTime;
    int duration;
};

class Process {
public:
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    bool completed;
    std::vector<IOEvent> ioEvents;

    Process(int id, int at, int bt, int prio = 0);

    void reset();
};

#endif
