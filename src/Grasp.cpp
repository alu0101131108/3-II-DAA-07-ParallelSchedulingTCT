#include "./../include/ScheduleAlgorithms/Grasp.hpp"

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
  std::vector<std::vector<Task>> schedules(machines.size(), std::vector<Task>());
  std::vector<int> scheduledTasksInd, taskIndCandidates, machIndCandidates, tctIncCandidates;
  int machIndex, taskIndex, candidateTctInc, glTctSummatory = 0;
  int previousTaskIndex, nodeTct, tctInc;

  while (scheduledTasksInd.size() != tasks.size())
  {
    // Find best k candidate insertions, minimize tct summatory.
    for (int k = 0; k < candidatesNumber_; k++)
    {
      if (scheduledTasksInd.size() + k == tasks.size()) 
        break;
      machIndex = -1;
      taskIndex = -1;
      candidateTctInc = UPPER_TIME_LIMIT;
      for (int m = 0; m < machines.size(); m++)
      {
        // Calculate tct of the last node in schedule of machine m (*).
        nodeTct = 0;
        for (int st = 0; st < schedules[m].size(); st++)
        {
          previousTaskIndex = (st == 0) ? 0 : schedules[m][st - 1].getId();
          nodeTct += setupTimes.get(previousTaskIndex, schedules[m][st].getId()) + schedules[m][st].getProcessTime();
        }
        for (int t = 1; t <= tasks.size(); t++)
        {
          // Check only tasks that are not scheduled nor flagged as candidates yet.
          if (std::find(scheduledTasksInd.begin(), scheduledTasksInd.end(), t) == scheduledTasksInd.end() &&
              std::find(taskIndCandidates.begin(), taskIndCandidates.end(), t) == taskIndCandidates.end())
          {
            // Calculate node t's tct in machine m if it's added, using previous node tct (*).
            previousTaskIndex = schedules[m].size() == 0 ? 0 : schedules[m][schedules[m].size() - 1].getId();
            tctInc = nodeTct + setupTimes.get(previousTaskIndex, t) + tasks[t - 1].getProcessTime();
            if (tctInc < candidateTctInc)
            {
              machIndex = m;
              taskIndex = t;
              candidateTctInc = tctInc;
            }
          }
        }
      }
      taskIndCandidates.push_back(taskIndex);
      machIndCandidates.push_back(machIndex);
      tctIncCandidates.push_back(candidateTctInc);
    }
    // Perform randomly one of the candidates insertions.
    int randomIndex = rand() % taskIndCandidates.size();
    schedules[machIndCandidates[randomIndex]].push_back(tasks[taskIndCandidates[randomIndex] - 1]);
    scheduledTasksInd.push_back(taskIndCandidates[randomIndex]);
    glTctSummatory += tctIncCandidates[randomIndex];
    taskIndCandidates.clear();
    machIndCandidates.clear();
    tctIncCandidates.clear();
  }
  // Set schedules into the environment machines.
  for (int m = 0; m < machines.size(); m++)
  {
    machines[m].setSchedule(schedules[m]);
  }
  env -> setMachines(machines);
  env -> setTctSum(glTctSummatory);
}

void Grasp::update(Environment *env)
{

}

void Grasp::run(Environment *env)
{
  constructive(env);
}