#include "Process.hpp"
#include <vector>

#include "Algorithms.hpp"

int selectRR(const std::vector<Process*>& readyQueue, int& rrPointer) {
    if (readyQueue.empty()) return -1;
    if (rrPointer >= (int)readyQueue.size()) rrPointer = 0;
    int idx = rrPointer;
    rrPointer = (rrPointer + 1) % readyQueue.size();
    return idx;
}
