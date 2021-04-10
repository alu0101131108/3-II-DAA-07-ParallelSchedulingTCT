#ifndef __CONSTRUCTIVEGREEDY_H__
#define __CONSTRUCTIVEGREEDY_H__
#include "ScheduleAlgorithm.hpp"
#include <iostream>

class ConstructiveGreedy : public ScheduleAlgorithm
{
  void run(const std::vector<Task> &tasks, std::vector<Machine> &machines, const Table &setupTimes);
};
#endif // __CONSTRUCTIVEGREEDY_H__