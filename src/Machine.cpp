#include "./../include/Machine.hpp"

Machine::Machine() 
{}

Machine::~Machine() 
{}

const std::vector<Task> &Machine::getSchedule() const
{
  return schedule_;
}

void Machine::setSchedule(std::vector<Task> newSchedule) 
{
  schedule_ = newSchedule;
}

void Machine::addToSchedule(const Task newTask) 
{
  schedule_.push_back(newTask);
}

void Machine::clearSchedule()
{
  schedule_.clear();
}


