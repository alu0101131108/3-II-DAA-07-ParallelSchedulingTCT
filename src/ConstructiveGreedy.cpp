#include "./../include/ConstructiveGreedy.hpp"

void ConstructiveGreedy::run(const std::vector<Task> &tasks, std::vector<Machine> &machines, const Table &setupTimes) 
{
  int nTasks = tasks.size();
  int nMachines = machines.size();
  std::vector<std::vector<Task>> schedules(nMachines, std::vector<Task>());
  std::vector<int> machineTCT(nMachines, 0);
  std::vector<int> scheduledIndexes;

  // Add one initial task for every machine.
  int minCompletionTime, minCtIndex;
  for (int m = 0; m < nMachines; m++)
  {
    minCompletionTime = UPPER_TIME_LIMIT;
    minCtIndex = -1;
    for (int j = 1; j < nTasks; j++)
    {
      // Check only tasks that are not scheduled yet.
      if (std::find(scheduledIndexes.begin(), scheduledIndexes.end(), j) == scheduledIndexes.end() &&
          (setupTimes.get(0, j) + tasks[j - 1].getProcessTime()) < minCompletionTime)
      {
        minCompletionTime = setupTimes.get(0, j) + tasks[j - 1].getProcessTime();
        minCtIndex = j;
      }
    }
    schedules[m].push_back(tasks[minCtIndex - 1]);
    machineTCT[m] = setupTimes.get(0, minCtIndex) + tasks[minCtIndex - 1].getProcessTime();
    scheduledIndexes.push_back(minCtIndex);
  }

  // Add tasks that minimize TCT to each machine.
  

  // Set schedules to corresponding machines.
  for (int m = 0; m < nMachines; m++)
  {
    machines[m].setSchedule(schedules[m]);
    std::cout << "TCT: " << machineTCT[m] << std::endl;
  }
}

// n: 5
// m: 4
// Pi: 10 23 71 11 14
// Sij:
// 0 2 3 8 5 6
// 8 0 5 8 9 9
// 9 7 0 8 3 7
// 7 5 8 0 3 2
// 1 1 2 4 0 8
// 4 7 9 0 1 0