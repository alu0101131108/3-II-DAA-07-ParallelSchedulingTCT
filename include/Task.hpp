#ifndef __TASK_H__
#define __TASK_H__
#include <iostream>

const int UPPER_TIME_LIMIT = 10000;

class Task
{
private:
  int processTime_;
  int id_;
public:
  Task(int id = -1, int processTime = 0);
  ~Task();
  void setProcessTime(int newTime);
  void setId(int newId);
  int getProcessTime() const;
  int getId() const;
  void print() const;
};

#endif // __TASK_H__
