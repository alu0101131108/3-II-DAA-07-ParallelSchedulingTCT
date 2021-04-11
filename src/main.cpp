#include "./../include/Environment.hpp"
#include "./../include/ConstructiveGreedy.hpp"

int main() {
  Environment env;
  env.loadProblemFromFile("./../input-problems/I40j_8m_S1_1.txt");
  env.printTasks();
  env.setScheduler(new ConstructiveGreedy());
  env.runScheduler();
  env.printMachineSchedules();
  return 0;
}