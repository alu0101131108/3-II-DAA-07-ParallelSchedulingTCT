#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__
#include "Task.hpp"
#include "Table.hpp"
#include "Machine.hpp"
#include "./ScheduleAlgorithms/ScheduleAlgorithm.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class Environment
{
private:
  std::vector<Task> tasks_;
  std::vector<Machine> machines_;
  Table setupTimes_;
  ScheduleAlgorithm *scheduler_;
  int tct_;

public:
  Environment();
  ~Environment();
  std::vector<Task> const& getTasks() const;
  std::vector<Machine> const& getMachines() const;
  Table const& getSetupTimes() const;
  int const getTct() const;
  void setTasks(std::vector<Task> newTaskList);
  void setMachines(std::vector<Machine> newMachineList);
  void setSetupTimes(Table newSetupTimes);
  void setScheduler(ScheduleAlgorithm *scheduleStrategy);
  void loadProblemFromFile(std::string filename);
  void runScheduler();
  void printTasks() const;
  void printMachineSchedules() const;
};

#endif // __SCHEDULER_H__