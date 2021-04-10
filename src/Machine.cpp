#include "./../include/Machine.hpp"

Machine::Machine() 
{}

Machine::~Machine() 
{}

std::vector<Task> const& Machine::getSchedule() const
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


