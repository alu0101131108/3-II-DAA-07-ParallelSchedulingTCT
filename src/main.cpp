#include "./../include/Environment.hpp"
#include "./../include/ScheduleAlgorithms/ConstructiveGreedy.hpp"
#include "./../include/ScheduleAlgorithms/AlternativeGreedy.hpp"
#include <vector>
#include <string>

int main() {
  Environment framework;

  for (int i = 2; i <= 8; i = i +2)
  {
    std::cout << "Tasks: 40, Machines: " << i << "S1_1." << std::endl; 
    framework.loadProblemFromFile("./../input-problems/I40j_" + std::to_string(i) + "m_S1_1.txt");
    framework.setScheduler(new ConstructiveGreedy());
    framework.runScheduler();
    std::cout << "Constructive-TCT: " << framework.getTct() << std::endl;
    framework.setScheduler(new AlternativeGreedy());
    framework.runScheduler();
    std::cout << "Alternative-TCT: " << framework.getTct() << std::endl;
  }

  return 0;
}