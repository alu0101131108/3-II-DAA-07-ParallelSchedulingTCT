#include "Grasp.hpp"

Grasp::Grasp(int threadsNumber, int operationType, int candidatesNumber, bool anxietyMode) :
    threadsNumber_(threadsNumber), operationType_(operationType), candidatesNumber_(candidatesNumber), anxietyMode_(anxietyMode) {}

Environment Grasp::interSwap(Environment *env)
{

  return *env;
}

Environment Grasp::intraSwap(Environment *env)
{

  return *env;
}

Environment Grasp::interInsert(Environment *env)
{

  return *env;
}

Environment Grasp::intraInsert(Environment *env)
{

  return *env;
}

void Grasp::constructive(Environment *env)
{
  const std::vector<Task> &tasks = (env->getTasks());
  std::vector<Machine> machines = (env->getMachines());
  const Table &setupTimes = (env->getSetupTimes());


}

void Grasp::update(Environment *env)
{
}