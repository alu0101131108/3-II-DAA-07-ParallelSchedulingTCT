#include "./../include/Environment.hpp"
#include "./../include/ConstructiveGreedy.hpp"

int main() {
  Environment env;
  env.loadProblemFromFile("./../input-problems/I40j_2m_S1_1.txt");
  env.setScheduler(new ConstructiveGreedy());
  env.runScheduler();
  env.printTasks();
  env.printMachineSchedules();
  return 0;
}