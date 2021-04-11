#include "./../include/Task.hpp"

Task::Task(int id, int processTime) : id_(id), processTime_(processTime)
{}

Task::~Task()
{}

void Task::setProcessTime(int newTime)
{
  processTime_ = newTime;
}

void Task::setId(int newId) 
{
  id_ = newId;
}

int Task::getProcessTime() const
{
  return processTime_;
}

int Task::getId() const
{
  return id_;
}

void Task::print() const
{
  std::cout << "[T" << id_ << ", Pt: " << processTime_ << "]";
}
