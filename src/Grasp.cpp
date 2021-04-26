#include "./../include/ScheduleAlgorithms/Grasp.hpp"

Grasp::Grasp(int threadsNumber, int operationType, int iterationsType, int candidatesNumber, bool anxiousMode) :
    threadsNumber_(threadsNumber), operationType_(operationType), iterationsType_(iterationsType),
    candidatesNumber_(candidatesNumber), anxiousMode_(anxiousMode)
{}

void Grasp::run(Environment *env)
{
  int threadIteration = 0;
  int tctSum, minTctSum = UPPER_TIME_LIMIT;
  Environment winnerEnv;
  bool noProgress;
  while (threadIteration < threadsNumber_)
  {
    noProgress = true;
    constructive(env);
    update(env);
    tctSum = env -> getTctSum();
    if (tctSum < minTctSum)
    {
      minTctSum = tctSum;
      winnerEnv = *env;
      noProgress = false;
    }
    switch (iterationsType_)
    {
    case ALL_ITERATIONS:
      threadIteration++;
      break;

    case NO_PROGRESS_ITERATIONS:
      if (noProgress)
        threadIteration++;
      break;

    default:
      std::cout << "ERROR: Unknown iterations type for Grasp.\n";
      throw 72;
    }
  }
  env -> copy(&winnerEnv);
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
  Environment previous, updated = *env;
  do
  {
    previous = updated;
    switch (operationType_)
    {
    case INTER_INSERT:
      interInsert(&updated);
      break;

    case INTRA_INSERT:
      intraInsert(&updated);
      break;

    case INTER_SWAP:
      interSwap(&updated);
      break;

    case INTRA_SWAP:
      intraSwap(&updated);
      break;

    default:
      std::cout << "ERROR: Unknown operation type for Grasp Algorithm." << std::endl;
      throw 1001;
      break;
    }
  } while (previous.getTctSum() != updated.getTctSum());
  env -> copy(&updated);
}

void Grasp::interSwap(Environment *env)
{
  const std::vector<Task> &tasks = (env->getTasks());
  const std::vector<Machine> &machines = (env->getMachines());
  bool anxiousFound = false;

  Environment tempEnv, minTctEnv = *env;
  int tempTctSum, minTctSum = env->getTctSum();

  for (int l = 0; l < machines.size(); l++)
  {
    for (int i = 0; i < machines.size(); i++)
    {
      if (l != i)
      {
        for (int j = 0; j < machines[l].getSchedule().size(); j++)
        {
          for (int k = 0; k < machines[i].getSchedule().size(); k++)
          {
            tempEnv = *env;
            tempEnv.swapScheduledTasks(l, j, i, k);
            tempEnv.computeTctSummatory();
            tempTctSum = tempEnv.getTctSum();
            if (tempTctSum < minTctSum)
            {
              minTctSum = tempTctSum;
              minTctEnv = tempEnv;
              if (anxiousMode_) 
              {
                anxiousFound = true;
                break;
              }
            }
          }
          if (anxiousFound) break;
        }
        if (anxiousFound) break;
      }
    }
    if (anxiousFound) break;
  }
  env->copy(&minTctEnv);
}

void Grasp::intraSwap(Environment *env)
{
  const std::vector<Task> &tasks = (env->getTasks());
  const std::vector<Machine> &machines = (env->getMachines());
  bool anxiousFound = false;

  Environment tempEnv, minTctEnv = *env;
  int tempTctSum, minTctSum = env->getTctSum();

  for (int i = 0; i < machines.size(); i++)
  {
    for (int j = 0; j < machines[i].getSchedule().size(); j++)
    {
      for (int k = 0; k < machines[i].getSchedule().size(); k++)
      {
        tempEnv = *env;
        tempEnv.swapScheduledTasks(i, j, i, k);
        tempEnv.computeTctSummatory();
        tempTctSum = tempEnv.getTctSum();
        if (tempTctSum < minTctSum)
        {
          minTctSum = tempTctSum;
          minTctEnv = tempEnv;
          if (anxiousMode_)
          {
            anxiousFound = true;
            break;
          }
        }
      }
      if (anxiousFound) break;
    }
    if (anxiousFound) break;
  }
  env -> copy(&minTctEnv);
}

void Grasp::interInsert(Environment *env)
{
  const std::vector<Task> &tasks = (env->getTasks());
  const std::vector<Machine> &machines = (env->getMachines());
  bool anxiousFound = false;

  Environment tempEnv, minTctEnv = *env;
  int tempTctSum, minTctSum = env->getTctSum();

  for (int l = 0; l < machines.size(); l++)
  {
    for (int i = 0; i < machines.size(); i++)
    {
      if (l != i)
      {
        for (int j = 0; j < machines[l].getSchedule().size(); j++)
        {
          for (int k = 0; k <= machines[i].getSchedule().size(); k++)
          {
            tempEnv = *env;
            tempEnv.insertScheduledTasks(l, j, i, k);
            tempEnv.computeTctSummatory();
            tempTctSum = tempEnv.getTctSum();
            if (tempTctSum < minTctSum)
            {
              minTctSum = tempTctSum;
              minTctEnv = tempEnv;
              if (anxiousMode_) 
              {
                anxiousFound = true;
                break;
              }
            }
          }
          if (anxiousFound) break;
        }
        if (anxiousFound) break;
      }
    }
    if (anxiousFound) break;
  }
  env->copy(&minTctEnv);
}

void Grasp::intraInsert(Environment *env)
{
  const std::vector<Task> &tasks = (env->getTasks());
  const std::vector<Machine> &machines = (env->getMachines());
  bool anxiousFound = false;

  Environment tempEnv, minTctEnv = *env;
  int tempTctSum, minTctSum = env->getTctSum();

  for (int i = 0; i < machines.size(); i++)
  {
    for (int j = 0; j < machines[i].getSchedule().size(); j++)
    {
      for (int k = 0; k <= machines[i].getSchedule().size(); k++)
      {
        tempEnv = *env;
        tempEnv.insertScheduledTasks(i, j, i, k);
        tempEnv.computeTctSummatory();
        tempTctSum = tempEnv.getTctSum();
        if (tempTctSum < minTctSum)
        {
          minTctSum = tempTctSum;
          minTctEnv = tempEnv;
          if (anxiousMode_)
          {
            anxiousFound = true;
            break;
          }
        }
      }
      if (anxiousFound) break;
    }
    if (anxiousFound) break;
  }
  env->copy(&minTctEnv);
}