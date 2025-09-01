#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <vector>
#include <string>

enum class ProcessState { NEW, READY, RUNNING, BLOCKED, COMPLETED };

// I/O event is triggered after the process has consumed `cpuPoint` units of CPU time
// (relative to this process's own execution), then it blocks for `duration` time units.
struct IOEvent {
    int cpuPoint;   // CPU time consumed so far when I/O should start
    int duration;   // how long the I/O takes (wall-clock time units)
};

class Process {
public:
    int pid;
    int arrivalTime;               // when it first appears in the system
    int burstTime;                 // total CPU burst required (units)
    int remainingTime;             // remaining CPU time
    int priority;                  // higher = higher priority
    int completionTime;            // wall-clock time when completed
    int firstStartTime;            // first time it ever got CPU (for response time)
    ProcessState state;

    std::vector<IOEvent> ioEvents; // sorted by cpuPoint ascending
    int ioIndex;                   // next IOEvent index
    int cpuConsumed;               // CPU time consumed so far (to trigger IO events)
    int unblockTime;               // wall-clock time when I/O will finish (if BLOCKED)
    int totalIODuration;           // sum of all IO durations (for waiting time metric)

    Process(int id, int at, int bt, int pr = 0, const std::vector<IOEvent>& io = {});
};

#endif
