#include "./../include/Environment.hpp"
#include "./../include/ConstructiveGreedy.hpp"

int main() {
  Environment env;
  env.loadProblemFromFile("./../input-problems/test.in");
  env.setScheduler(new ConstructiveGreedy());
  env.runScheduler();
  env.printTasks();
  env.printMachineSchedules();
  return 0;
}