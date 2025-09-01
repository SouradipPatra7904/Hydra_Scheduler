#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include "Process.hpp"

// return index within readyQueue (0..size-1), or -1 if empty
int selectFCFS(const std::vector<Process*>& readyQueue, int /*unused*/);
int selectSJF(const std::vector<Process*>& readyQueue, int /*unused*/);
int selectPriority(const std::vector<Process*>& readyQueue, int /*unused*/);
int selectRR(const std::vector<Process*>& readyQueue, int& rrPointer);

#endif
//end
