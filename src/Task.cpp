#include "./../include/Task.hpp"

Task::Task(int processTime) : processTime_(processTime)
{}

Task::~Task()
{}

void Task::setProcessTime(int newTime)
{
  processTime_ = newTime;
}

int Task::getProcessTime() const
{
  return processTime_;
}
