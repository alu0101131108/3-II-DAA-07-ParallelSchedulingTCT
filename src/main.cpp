#include "./../include/Environment.hpp"
#include "./../include/ScheduleAlgorithms/ConstructiveGreedy.hpp"
#include "./../include/ScheduleAlgorithms/AlternativeGreedy.hpp"
#include "./../include/ScheduleAlgorithms/Grasp.hpp"
#include "./../include/ScheduleAlgorithms/Gvns.hpp"
#include <vector>
#include <string>

// Operation types: INTER_INSERT, INTRA_INSERT, INTRA_SWAP and INTER_SWAP.
// Iteration mode: ALL_ITERATIONS and NO_PROGRESS_ITERATIONS.
int main() {
  srand(time(NULL));
  Environment framework;


  //////////// Test all test inputs with each algorithm.
  for (int i = 2; i <= 8; i = i +2)
  {
    std::cout << "\n\n==========Tasks: 40, Machines: " << i << ", S1_1.==========" << std::endl;
    framework.loadProblemFromFile("./../input-problems/I40j_" + std::to_string(i) + "m_S1_1.txt");

    framework.setScheduler(new ConstructiveGreedy());
    framework.runScheduler();
    framework.computeTctSummatory();
    std::cout << "\n----------Constructive-TCT: " << framework.getTctSum() << "----------" << std::endl;

    framework.setScheduler(new AlternativeGreedy());
    framework.runScheduler();
    framework.computeTctSummatory();
    std::cout << "\n----------Alternative-TCT: " << framework.getTctSum() << "----------" << std::endl;

    framework.setScheduler(new Grasp(100, INTER_SWAP, ALL_ITERATIONS, 4, false));
    framework.runScheduler();
    framework.computeTctSummatory();
    std::cout << "\n----------Grasp-IntraSwap-TCT: " << framework.getTctSum() << "----------" << std::endl;

    framework.setScheduler(new Grasp(100, INTRA_INSERT, ALL_ITERATIONS, 4, false));
    framework.runScheduler();
    framework.computeTctSummatory();
    std::cout << "\n----------Grasp-IntraInsert-TCT: " << framework.getTctSum() << "----------" << std::endl;

    framework.setScheduler(new Grasp(100, INTRA_SWAP, ALL_ITERATIONS, 4, false));
    framework.runScheduler();
    framework.computeTctSummatory();
    std::cout << "\n----------Grasp-InterSwap-TCT: " << framework.getTctSum() << "----------" << std::endl;

    framework.setScheduler(new Grasp(100, INTER_INSERT, ALL_ITERATIONS, 4, false));
    framework.runScheduler();
    framework.computeTctSummatory();
    std::cout << "\n----------Grasp-InterInsert-TCT: " << framework.getTctSum() << "----------" << std::endl;

    framework.setScheduler(new Gnvs(50, ALL_ITERATIONS, INTER_INSERT, 5, false));
    framework.runScheduler();
    framework.computeTctSummatory();
    std::cout << "\n----------GNVS-TCT: " << framework.getTctSum() << "----------" << std::endl;
  }

  return 0;
}