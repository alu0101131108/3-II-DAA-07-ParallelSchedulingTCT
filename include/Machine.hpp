#ifndef __MACHINE_H__
#define __MACHINE_H__
#include "Task.hpp"
#include <vector>

class Machine
{
private:
  std::vector<Task> schedule_;
public:
  Machine();
  ~Machine();
  std::vector<Task> const& getSchedule() const;
  void setSchedule(std::vector<Task> newSchedule);
  void addToSchedule(const Task newTask);
  void clearSchedule();
};

#endif // __MACHINE_H__