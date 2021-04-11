#include "./../include/AlternativeGreedy.hpp"

void AlternativeGreedy::run(const std::vector<Task> &tasks, std::vector<Machine> &machines, const Table &setupTimes, int &tct)
{
  int nTasks = tasks.size();
  int nMachines = machines.size();
  int totalCt = 0;
  std::vector<std::vector<Task>> schedules(nMachines, std::vector<Task>());
  std::vector<int> scheduledIndexes;

  // Search, for each machine, the task that does fewer increment to its completion time when added to its schedule.
  int minTCtTask, minTCtInc, minCtMachineIndex; // For the outter search. Best machine to insert its own best task to insert.
  int minCtInc, minCtTask, lastTask;            // For the inner search. Best task to insert for each machine.
  while (scheduledIndexes.size() < nTasks)
  {
    minTCtInc = UPPER_TIME_LIMIT;
    for (int m = 0; m < nMachines; m++)
    {
      lastTask = schedules[m].size() == 0 ? 0 : schedules[m][schedules[m].size() - 1].getId();
      minCtInc = UPPER_TIME_LIMIT;
      for (int j = 1; j < nTasks; j++)
      {
        // Check only tasks that are not scheduled yet.
        if (std::find(scheduledIndexes.begin(), scheduledIndexes.end(), j) == scheduledIndexes.end() &&
            (setupTimes.get(lastTask, j) + tasks[j - 1].getProcessTime()) < minCtInc)
        {
          minCtInc = setupTimes.get(lastTask, j) + tasks[j - 1].getProcessTime();
          minCtTask = j;
        }
      }
      if (minCtInc < minTCtInc)
      {
        minTCtInc = minCtInc;
        minCtMachineIndex = m;
        minTCtTask = minCtTask;
      }
    }
    schedules[minCtMachineIndex].push_back(tasks[minTCtTask - 1]);
    totalCt += minTCtInc;
    scheduledIndexes.push_back(minTCtTask);
  }

  // Set schedules to corresponding machines.
  for (int m = 0; m < nMachines; m++)
  {
    machines[m].setSchedule(schedules[m]);
  }
  tct = totalCt;
}
