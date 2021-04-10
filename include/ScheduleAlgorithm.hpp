#ifndef __SCHEDULEALGORITHM_H__
#define __SCHEDULEALGORITHM_H__
#include "Table.hpp"
#include "Task.hpp"
#include "Machine.hpp"
class ScheduleAlgorithm
{
public:
  virtual void run(const std::vector<Task> &tasks, std::vector<Machine> &machines, const Table &setupTimes) = 0;
};

#endif // __SCHEDULEALGORITHM_H__