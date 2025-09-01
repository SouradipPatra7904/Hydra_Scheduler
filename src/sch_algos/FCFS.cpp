#include "Process.hpp"
#include "Algorithms.hpp"
#include <limits>

// FCFS: earliest arrival first (stable). We assume readyQueue filled only with READY processes.
// Since readyQueue is append-on-arrival order, just pick 0.
int selectFCFS(const std::vector<Process*>& readyQueue, int) {
    if (readyQueue.empty()) return -1;
    return 0;
}
