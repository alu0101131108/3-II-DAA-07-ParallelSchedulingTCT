#ifndef __CONSTRUCTIVEGREEDY_H__
#define __CONSTRUCTIVEGREEDY_H__
#include "ScheduleAlgorithm.hpp"
#include <vector>
#include <algorithm>

class ConstructiveGreedy : public ScheduleAlgorithm
{
  void run(const std::vector<Task> &tasks, std::vector<Machine> &machines, const Table &setupTimes, int &tct);
};
#endif // __CONSTRUCTIVEGREEDY_H__