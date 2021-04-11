#include "./../include/ConstructiveGreedy.hpp"

void ConstructiveGreedy::run(const std::vector<Task> &tasks, std::vector<Machine> &machines, const Table &setupTimes) 
{
  int nTasks = tasks.size();
  int nMachines = machines.size();
  std::vector<int> scheduledTasks;
  
  // Add one initial task for every machine.
  int minProcessTime, minPtIndex;
  for (int m = 0; m < nMachines; m++)
  {
    minProcessTime = UPPER_PT_LIMIT;
    minPtIndex = -1;
    for (int j = 1; j < nTasks; j++)
    {
      // Check only tasks that are not scheduled yet.
      if (std::find(scheduledTasks.begin(), scheduledTasks.end(), j) == scheduledTasks.end() &&
          setupTimes.get(0, j) < minProcessTime)
      {
        minProcessTime = setupTimes.get(0, j);
        minPtIndex = j;
      }
    }
    machines[m].addToSchedule(tasks[minPtIndex - 1]);
    scheduledTasks.push_back(minPtIndex);
  }

  // Add tasks that minimize TCT to each machine.
  
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