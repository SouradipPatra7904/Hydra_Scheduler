#include "Process.hpp"
#include <vector>
#include <algorithm>
#include "Algorithms.hpp"

// #include "SJF.hpp"
#include <limits>

// Shortest-Job-First selection from the readyQueue (non-preemptive).
// Returns index inside readyQueue, or -1 if empty.
int selectSJF(const std::vector<Process*>& readyQueue, int /*unused*/) {
    if (readyQueue.empty()) return -1;
    int bestIdx = 0;
    int bestRem = readyQueue[0]->remainingTime;
    for (int i = 1; i < (int)readyQueue.size(); ++i) {
        // prefer smaller remaining time; tie-breaker: lower PID
        int rem = readyQueue[i]->remainingTime;
        if (rem < bestRem || (rem == bestRem && readyQueue[i]->pid < readyQueue[bestIdx]->pid)) {
            bestRem = rem;
            bestIdx = i;
        }
    }
    return bestIdx;
}

