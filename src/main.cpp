#include "./../include/Environment.hpp"
#include "./../include/ScheduleAlgorithms/ConstructiveGreedy.hpp"
#include "./../include/ScheduleAlgorithms/AlternativeGreedy.hpp"

int main() {
  Environment env;
  
  env.loadProblemFromFile("./../input-problems/I40j_8m_S1_1.txt");
  env.setScheduler(new ConstructiveGreedy());
  env.runScheduler();
  std::cout << "Constructive-TCT: " << env.getTct() << std::endl;

  env.loadProblemFromFile("./../input-problems/I40j_8m_S1_1.txt");
  env.setScheduler(new AlternativeGreedy());
  env.runScheduler();
  std::cout << "Alternative-TCT: " << env.getTct() << std::endl;

  return 0;
}