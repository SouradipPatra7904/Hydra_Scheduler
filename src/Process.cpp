#include "Process.hpp"

Process::Process(int id, int at, int bt, int prio)
    : pid(id), arrivalTime(at), burstTime(bt), priority(prio) {
    reset();
}

void Process::reset() {
    remainingTime = burstTime;
    completionTime = waitingTime = turnaroundTime = 0;
    completed = false;
}
