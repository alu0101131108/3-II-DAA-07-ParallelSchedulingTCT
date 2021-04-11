#ifndef __ALTERNATIVEGREEDY_H__
#define __ALTERNATIVEGREEDY_H__
#include "ScheduleAlgorithm.hpp"
#include <vector>
#include <algorithm>

class AlternativeGreedy : public ScheduleAlgorithm
{
  void run(const std::vector<Task> &tasks, std::vector<Machine> &machines, const Table &setupTimes, int &tct);
};
#endif // __ALTERNATIVEGREEDY_H__