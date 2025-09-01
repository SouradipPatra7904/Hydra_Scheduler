#include "Process.hpp"

Process::Process(int id, int at, int bt, int pr, const std::vector<IOEvent>& io)
    : pid(id),
      arrivalTime(at),
      burstTime(bt),
      remainingTime(bt),
      priority(pr),
      completionTime(0),
      firstStartTime(-1),
      state(ProcessState::NEW),
      ioEvents(io),
      ioIndex(0),
      cpuConsumed(0),
      unblockTime(-1),
      totalIODuration(0)
{
    for (const auto& e : ioEvents) totalIODuration += e.duration;
}
