#include "./../include/Environment.hpp"
#include "./../include/ScheduleAlgorithms/ConstructiveGreedy.hpp"
#include "./../include/ScheduleAlgorithms/AlternativeGreedy.hpp"
#include "./../include/ScheduleAlgorithms/Grasp.hpp"
#include <vector>
#include <string>

int main() {
  Environment framework;

  for (int i = 2; i <= 8; i = i +2)
  {
    std::cout << "\n\n==========Tasks: 40, Machines: " << i << ", S1_1.==========" << std::endl;
    framework.loadProblemFromFile("./../input-problems/I40j_" + std::to_string(i) + "m_S1_1.txt");
    framework.setScheduler(new ConstructiveGreedy());
    framework.runScheduler();
    std::cout << "\n----------Constructive-TCT: " << framework.getTctSum() << "----------" << std::endl;
    // framework.printMachineSchedules();
    framework.setScheduler(new AlternativeGreedy());
    framework.runScheduler();
    std::cout << "\n----------Alternative-TCT: " << framework.getTctSum() << "----------" << std::endl;
    // framework.printMachineSchedules();
  }

  return 0;
}