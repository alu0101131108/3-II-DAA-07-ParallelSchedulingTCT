#include "./../include/ScheduleAlgorithms/ConstructiveGreedy.hpp"

void ConstructiveGreedy::run(Environment *env) // const std::vector<Task> &tasks, std::vector<Machine> &machines, const Table &setupTimes, int &tct
{
  const std::vector<Task> &tasks = (env -> getTasks());
  std::vector<Machine> machines = (env -> getMachines());
  const Table &setupTimes = (env -> getSetupTimes());

  int nTasks = tasks.size();
  int nMachines = machines.size();
  int nodeTct, glTct = 0;
  std::vector<std::vector<Task>> schedules(nMachines, std::vector<Task>());
  std::vector<int> scheduledIndexes;

  // Add one initial task for every machine.
  int minTctInc, taskIndex;
  for (int m = 0; m < nMachines; m++)
  {
    minTctInc = UPPER_TIME_LIMIT;
    for (int j = 1; j <= nTasks; j++)
    {
      // Check only tasks that are not scheduled yet.
      if (std::find(scheduledIndexes.begin(), scheduledIndexes.end(), j) == scheduledIndexes.end() &&
          (setupTimes.get(0, j) + tasks[j - 1].getProcessTime()) < minTctInc)
      {
        minTctInc = setupTimes.get(0, j) + tasks[j - 1].getProcessTime();
        taskIndex = j;
      }
    }
    schedules[m].push_back(tasks[taskIndex - 1]);
    nodeTct = minTctInc;
    glTct += nodeTct;
    scheduledIndexes.push_back(taskIndex);
  }

  // Search, for each machine, the task that does fewer increment to its tct when added to its schedule.
  // Then, among those, perform the insertion that does fewer increment to the global tct. 
  int glTaskIndex, glMinTctInc, glMachIndex;  // For the outter search. Best machine to insert its own best task to insert.
  int tempTctInc, lastTask;                   // For the inner search. Best task to insert for each machine. (Also minTctInc, taskIndex)
  while (scheduledIndexes.size() < nTasks)
  {
    glMinTctInc = UPPER_TIME_LIMIT;
    for (int m = 0; m < nMachines; m++)
    {
      lastTask = schedules[m][schedules[m].size() - 1].getId();
      minTctInc = UPPER_TIME_LIMIT;

      // Look for the best task to insert in the machine m.
      for (int j = 1; j <= nTasks; j++)
      {
        // Calculate tct to node j.
        nodeTct = 0;
        for (int st = 0; st < schedules[m].size(); st++)
        {
          // Sumattory of each process + setup time in scheduled tasks.
          if (st == 0)
          {
            nodeTct += setupTimes.get(0, schedules[m][st].getId()) + schedules[m][st].getProcessTime();
          }
          else 
          {
            nodeTct += setupTimes.get(schedules[m][st - 1].getId(), schedules[m][st].getId()) + schedules[m][st].getProcessTime();
          }
        }
        nodeTct += setupTimes.get(lastTask, j) + tasks[j - 1].getProcessTime();
        tempTctInc = nodeTct;
        // Check only tasks that are not scheduled yet.
        if (std::find(scheduledIndexes.begin(), scheduledIndexes.end(), j) == scheduledIndexes.end() &&
            tempTctInc < minTctInc)
        {
          minTctInc = tempTctInc;
          taskIndex = j;
        }
      }

      if (minTctInc < glMinTctInc)
      {
        glMinTctInc = minTctInc;
        glMachIndex = m;
        glTaskIndex = taskIndex;
      }
    }
    schedules[glMachIndex].push_back(tasks[glTaskIndex - 1]);
    // Calculate tct to node glTaskIndex.
    nodeTct = 0;
    for (int st = 0; st < schedules[glMachIndex].size(); st++)
    {
      // Sumattory of each process + setup time in scheduled tasks untill glTaskIndex.
      lastTask = st == 0 ? 0 : schedules[glMachIndex][st - 1].getId();
      nodeTct += setupTimes.get(lastTask, schedules[glMachIndex][st].getId()) + schedules[glMachIndex][st].getProcessTime();
    }
    glTct += nodeTct;
    scheduledIndexes.push_back(glTaskIndex);
  }

  // Set schedules to corresponding machines.
  for (int m = 0; m < nMachines; m++)
  {
    machines[m].setSchedule(schedules[m]);
  }
  env -> setMachines(machines);
  env -> setTctSum(glTct);
}
