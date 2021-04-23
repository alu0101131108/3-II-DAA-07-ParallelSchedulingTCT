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

class ScheduleAlgorithm;
class Environment
{
private:
  std::vector<Task> tasks_;
  std::vector<Machine> machines_;
  Table setupTimes_;
  ScheduleAlgorithm *scheduler_;
  int tctSum_;

public:
  Environment();
  ~Environment();
  const std::vector<Task>& getTasks() const;
  const std::vector<Machine>& getMachines() const;
  const Table& getSetupTimes() const;
  const int getTctSum() const;
  void setTasks(std::vector<Task> newTaskList);
  void setMachines(std::vector<Machine> newMachineList);
  void setSetupTimes(Table newSetupTimes);
  void setScheduler(ScheduleAlgorithm *scheduleStrategy);
  void setTctSum(int newTctSum);

  void loadProblemFromFile(std::string filename);
  void runScheduler();
  void printTasks() const;
  void printMachineSchedules() const;
};

#endif // __SCHEDULER_H__