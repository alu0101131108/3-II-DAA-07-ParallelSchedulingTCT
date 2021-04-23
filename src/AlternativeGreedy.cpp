#include "./../include/ScheduleAlgorithms/AlternativeGreedy.hpp"

void AlternativeGreedy::run(Environment *env)
{
  const std::vector<Task> &tasks = (env->getTasks());
  std::vector<Machine> machines = (env->getMachines());
  const Table &setupTimes = (env->getSetupTimes());

  int nTasks = tasks.size();
  int nMachines = machines.size();
  int nodeTct, glTct = 0;
  std::vector<std::vector<Task>> schedules(nMachines, std::vector<Task>());
  std::vector<int> scheduledIndexes;

  // Search, for each machine, the task that does fewer increment to its tct when added to its schedule.
  // Then, perform each insertion.
  int minTctInc, taskIndex, tempTctInc, lastTask; // Best task to insert for each machine.
  while (scheduledIndexes.size() < nTasks)
  {
    for (int m = 0; m < nMachines; m++)
    {
      // In case there are no more tasks to insert, break the loop.
      if (scheduledIndexes.size() >= nTasks) break;
      
      lastTask = schedules[m].size() == 0 ? 0 : schedules[m][schedules[m].size() - 1].getId();
      minTctInc = UPPER_TIME_LIMIT;
      // Look for the best task to insert in the machine m.
      for (int j = 1; j <= nTasks; j++)
      {
        tempTctInc = setupTimes.get(lastTask, j) + tasks[j - 1].getProcessTime();
        // Check only tasks that are not scheduled yet.
        if (std::find(scheduledIndexes.begin(), scheduledIndexes.end(), j) == scheduledIndexes.end() &&
            tempTctInc < minTctInc)
        {
          minTctInc = tempTctInc;
          taskIndex = j;
        }
      }
      // Insert given best task for machine m.
      schedules[m].push_back(tasks[taskIndex - 1]);
      scheduledIndexes.push_back(taskIndex);
      // Calculate tct to the node inserted and add it to the global tct.
      nodeTct = 0;
      for (int st = 0; st < schedules[m].size(); st++)
      {
        // Sumattory of each process + setup time in scheduled tasks untill glTaskIndex.
        lastTask = st == 0 ? 0 : schedules[m][st - 1].getId();
        nodeTct += setupTimes.get(lastTask, schedules[m][st].getId()) + schedules[m][st].getProcessTime();
      }
      glTct += nodeTct;
    }  
  }

  // Set schedules to corresponding machines.
  for (int m = 0; m < nMachines; m++)
  {
    machines[m].setSchedule(schedules[m]);
  }
  env->setMachines(machines);
  env->setTctSum(glTct);
}
