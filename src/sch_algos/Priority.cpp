#include "Process.hpp"
#include <vector>
#include "Algorithms.hpp"

int selectPriority(const std::vector<Process*>& readyQueue, int) {
    if (readyQueue.empty()) return -1;
    int idx = 0;
    int best = readyQueue[0]->priority;
    for (int i = 1; i < (int)readyQueue.size(); ++i) {
        if (readyQueue[i]->priority > best) {
            best = readyQueue[i]->priority;
            idx = i;
        }
    }
    return idx;
}
