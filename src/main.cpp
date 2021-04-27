#include "./../include/Environment.hpp"
#include "./../include/ScheduleAlgorithms/ConstructiveGreedy.hpp"
#include "./../include/ScheduleAlgorithms/AlternativeGreedy.hpp"
#include "./../include/ScheduleAlgorithms/Grasp.hpp"
#include "./../include/ScheduleAlgorithms/Gvns.hpp"
#include <vector>
#include <string>
#include <chrono>

// Tab helper for table construction.
std::string tab(std::string str, int size)
{
  int nSpaces = size - str.size();
  std::string extra(nSpaces, ' '); 
  return str + extra;
}

// Operation types: INTER_INSERT, INTRA_INSERT, INTRA_SWAP and INTER_SWAP.
// Iteration mode: ALL_ITERATIONS and NO_PROGRESS_ITERATIONS.

int main() 
{
  srand(time(NULL));
  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double> elapsed_seconds;
  Environment framework;

  char option;
  std::cout << "Please select one of the following problem inputs. 1-4 (Stored at input-problems/)\n";
  std::cout << "(1) I40j_2m_S1_1.txt\n";
  std::cout << "(2) I40j_4m_S1_1.txt\n";
  std::cout << "(3) I40j_6m_S1_1.txt\n";
  std::cout << "(4) I40j_8m_S1_1.txt\n";
  std::cin >> option;

  switch (option)
  {
  case '1':
    framework.loadProblemFromFile("./../input-problems/I40j_2m_S1_1.txt");
    break;

  case '2':
    framework.loadProblemFromFile("./../input-problems/I40j_4m_S1_1.txt");
    break;

  case '3':
    framework.loadProblemFromFile("./../input-problems/I40j_6m_S1_1.txt");
    break;

  case '4':
    framework.loadProblemFromFile("./../input-problems/I40j_8m_S1_1.txt");
    break;

  default:
    std::cout << "ERROR: Non valid option in main().\n";
    throw 30;
    break;
  }

  std::cout << "Please select one of the following Algorithms\n";
  std::cout << "(1) Constructive Greedy\n";
  std::cout << "(2) Alternative Greedy\n";
  std::cout << "(3) GRASP\n";
  std::cout << "(4) GVNS\n";
  std::cin >> option;

  int iterations, operationType, iterationType, candidatesNumber, anxiousMode, kMax;
  bool anxious;

  switch (option)
  {
  case '1':
    framework.setScheduler(new ConstructiveGreedy());
    break;

  case '2':
    framework.setScheduler(new AlternativeGreedy());
    break;

  case '3':
    std::cout << "Select number of iterations: ";
    std::cin >> iterations;
    std::cout << "Select operation type:\n";
    std::cout << "(0) Intra Reinsert.\n";
    std::cout << "(1) Intra Swap.\n";
    std::cout << "(2) Inter Reinsert.\n";
    std::cout << "(3) Inter Swap.\n";
    std::cin >> operationType;
    std::cout << "Select iteration counting mode:\n";
    std::cout << "(0) Normal.\n";
    std::cout << "(1) No Progress Only.\n";
    std::cin >> iterationType;
    std::cout << "Select candidates number (k): ";
    std::cin >> candidatesNumber;
    std::cout << "Select anxious mode:\n";
    std::cout << "(0) Off.\n";
    std::cout << "(1) On.\n";
    std::cin >> anxiousMode;
    anxious = anxiousMode == 0 ? false : true;
    framework.setScheduler(new Grasp(iterations, operationType, iterationType, candidatesNumber, anxious));
    break;

  case '4':
    std::cout << "Select number of iterations: ";
    std::cin >> iterations;
    std::cout << "Select operation type:\n";
    std::cout << "(0) Intra Reinsert.\n";
    std::cout << "(1) Intra Swap.\n";
    std::cout << "(2) Inter Reinsert.\n";
    std::cout << "(3) Inter Swap.\n";
    std::cin >> operationType;
    std::cout << "Select iteration counting mode:\n";
    std::cout << "(0) Normal.\n";
    std::cout << "(1) No Progress Only.\n";
    std::cin >> iterationType;
    std::cout << "Select anxious mode:\n";
    std::cout << "(0) Off.\n";
    std::cout << "(1) On.\n";
    std::cin >> anxiousMode;
    anxious = anxiousMode == 0 ? false : true;
    std::cout << "Select kMax value: ";
    std::cin >> kMax;
    framework.setScheduler(new Gnvs(iterations, iterationType, operationType, kMax, anxious));
    break;

  default:
    std::cout << "ERROR: Non valid option in main().\n";
    throw 30;
    break;
  }

  std::cout << "Running scheduler algorithm, this may take a while...\n";
  start = std::chrono::high_resolution_clock::now();
  framework.runScheduler();
  end = std::chrono::high_resolution_clock::now();
  elapsed_seconds = end - start;
  framework.computeTctSummatory();

  std::cout << "Done in " << elapsed_seconds.count() << " seconds.\n";
  std::cout << "Sum of every machine's TCT is " << framework.getTctSum() << std::endl;
  std::cout << "Final schedules:\n";
  framework.printMachineSchedules();

  return 0;
}

///////////////////////////////////////////////////////////
//////////// GVNS - Normal/NoProgress - NonAnxious/Anxious
///////////////////////////////////////////////////////////
// srand(time(NULL));
// std::chrono::time_point<std::chrono::system_clock> start, end;
// std::chrono::duration<double> elapsed_seconds;
// Environment framework;
// std::string cpuTime;
// std::vector<int> iterations = {10, 50, 100, 200};
// std::vector<int> operation = {INTER_SWAP, INTER_INSERT};
// std::vector<int> kMaxValues = {2, 5, 10};
// std::string opString;

// for (int m = 2; m <= 8; m = m + 2)
// {
//   for (int it = 0; it < iterations.size(); it++)
//   {
//     for (int km = 0; km < kMaxValues.size(); km++)
//       {
//         for (int op = 0; op < operation.size(); op++)
//         {
//           framework.loadProblemFromFile("./../input-problems/I40j_" + std::to_string(m) + "m_S1_1.txt");
//           framework.setScheduler(new Gnvs(iterations[it], NO_PROGRESS_ITERATIONS, operation[op], kMaxValues[km], true));
//           start = std::chrono::high_resolution_clock::now();
//           framework.runScheduler();
//           end = std::chrono::high_resolution_clock::now();
//           elapsed_seconds = end - start;
//           framework.computeTctSummatory();
//           cpuTime = std::to_string(elapsed_seconds.count());

//           switch (operation[op])
//           {
//           case INTER_INSERT:
//             opString = "Inter-Insert";
//             break;
//           case INTRA_INSERT:
//             opString = "Intra-Insert";
//             break;
//           case INTER_SWAP:
//             opString = "Inter-Swap";
//             break;
//           case INTRA_SWAP:
//             opString = "Intra-Swap";
//             break;
//           }
//           std::cout << tab(std::to_string(m), 3) + tab(std::to_string(iterations[it]), 6) + tab(std::to_string(kMaxValues[km]), 5) + tab(opString, 14) + tab(std::to_string(framework.getTctSum()), 7) + tab(cpuTime, 12) << std::endl;
//         }
//       }
//   }
// }
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//////////// GRASP - Normal/NoProgress - NonAnxious/Anxious
///////////////////////////////////////////////////////////
// srand(time(NULL));
// std::chrono::time_point<std::chrono::system_clock> start, end;
// std::chrono::duration<double> elapsed_seconds;
// Environment framework;
// std::string cpuTime;
// std::vector<int> iterations = {10, 50, 100, 200, 500, 1000};
// std::vector<int> operation = {INTRA_SWAP, INTRA_INSERT, INTER_SWAP, INTER_INSERT};
// std::string opString;

// for (int m = 2; m <= 8; m = m + 2)
// {
//   for (int it = 0; it < iterations.size(); it++)
//   {
//     for (int op = 0; op < operation.size(); op++)
//     {
//       framework.loadProblemFromFile("./../input-problems/I40j_" + std::to_string(m) + "m_S1_1.txt");
//       framework.setScheduler(new Grasp(iterations[it], operation[op], NO_PROGRESS_ITERATIONS, 4, true));
//       start = std::chrono::high_resolution_clock::now();
//       framework.runScheduler();
//       end = std::chrono::high_resolution_clock::now();
//       elapsed_seconds = end - start;
//       framework.computeTctSummatory();
//       cpuTime = std::to_string(elapsed_seconds.count());

//       switch (operation[op])
//       {
//       case INTER_INSERT:
//         opString =  "Inter-Insert";
//         break;
//       case INTRA_INSERT:
//         opString = "Intra-Insert";
//         break;
//       case INTER_SWAP:
//         opString = "Inter-Swap";
//         break;
//       case INTRA_SWAP:
//         opString = "Intra-Swap";
//         break;
//       }
//       std::cout << tab(std::to_string(m), 3) + tab(std::to_string(iterations[it]), 6) + tab(opString, 14) + tab(std::to_string(framework.getTctSum()), 7) + tab(cpuTime, 12) << std::endl;
//     }
//   }
// }
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//////////// Alternative Greedy tests
///////////////////////////////////////////////////////////
// srand(time(NULL));
// std::chrono::time_point<std::chrono::system_clock> start, end;
// std::chrono::duration<double> elapsed_seconds;
// Environment framework;
// std::string cpuTime;
// for (int i = 2; i <= 8; i = i + 2)
// {
//   for (int j = 0; j < 5; j++)
//   {
//     framework.loadProblemFromFile("./../input-problems/I40j_" + std::to_string(i) + "m_S1_1.txt");
//     framework.setScheduler(new AlternativeGreedy());
//     start = std::chrono::high_resolution_clock::now();
//     framework.runScheduler();
//     end = std::chrono::high_resolution_clock::now();
//     elapsed_seconds = end - start;
//     framework.computeTctSummatory();
//     cpuTime = std::to_string(elapsed_seconds.count());
//     for (int c = 0; c < cpuTime.size(); c++)
//       if (cpuTime[c] == '.')
//       {
//         cpuTime[c] = ',';
//         break;
//       }
//
//     std::cout << "n = 40, m = " << i << ", Ex = " << j + 1 << ".\n";
//     std::cout << framework.getTctSum() << " " << cpuTime << std::endl;
//   }
// }
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//////////// Constructive Greedy tests
///////////////////////////////////////////////////////////
// srand(time(NULL));
// std::chrono::time_point<std::chrono::system_clock> start, end;
// std::chrono::duration<double> elapsed_seconds;
// Environment framework;
// std::string cpuTime;
// for (int i = 2; i <= 8; i = i + 2)
// {
//   for (int j = 0; j < 5; j++)
//   {
//     framework.loadProblemFromFile("./../input-problems/I40j_" + std::to_string(i) + "m_S1_1.txt");
//     framework.setScheduler(new ConstructiveGreedy());
//     start = std::chrono::high_resolution_clock::now();
//     framework.runScheduler();
//     end = std::chrono::high_resolution_clock::now();
//     elapsed_seconds = end - start;
//     framework.computeTctSummatory();
//     cpuTime = std::to_string(elapsed_seconds.count());
//     for (int c = 0; c < cpuTime.size(); c++)
//       if (cpuTime[c] == '.')
//       {
//         cpuTime[c] = ',';
//         break;
//       }
//
//     std::cout << "n = 40, m = " << i << ", Ex = " << j << ".\n";
//     std::cout << framework.getTctSum() << " " << cpuTime << std::endl;
//   }
// }
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//////////// Test all test inputs with each algorithm.
//////////// With non concrete parameter specification.
///////////////////////////////////////////////////////////
// srand(time(NULL));
// std::chrono::time_point<std::chrono::system_clock> start, end;
// std::chrono::duration<double> elapsed_seconds;
// Environment framework;
// std::string cpuTime;
// for (int i = 2; i <= 8; i = i +2)
// {
//   std::cout << "\n\n==========Tasks: 40, Machines: " << i << ", S1_1.==========" << std::endl;
//   framework.loadProblemFromFile("./../input-problems/I40j_" + std::to_string(i) + "m_S1_1.txt");
//
//   framework.setScheduler(new ConstructiveGreedy());
//   framework.runScheduler();
//   framework.computeTctSummatory();
//   std::cout << "\n----------Constructive-TCT: " << framework.getTctSum() << "----------" << std::endl;
//
//   framework.setScheduler(new AlternativeGreedy());
//   framework.runScheduler();
//   framework.computeTctSummatory();
//   std::cout << "\n----------Alternative-TCT: " << framework.getTctSum() << "----------" << std::endl;
//
//   framework.setScheduler(new Grasp(100, INTER_SWAP, ALL_ITERATIONS, 4, false));
//   framework.runScheduler();
//   framework.computeTctSummatory();
//   std::cout << "\n----------Grasp-IntraSwap-TCT: " << framework.getTctSum() << "----------" << std::endl;
//
//   framework.setScheduler(new Grasp(100, INTRA_INSERT, ALL_ITERATIONS, 4, false));
//   framework.runScheduler();
//   framework.computeTctSummatory();
//   std::cout << "\n----------Grasp-IntraInsert-TCT: " << framework.getTctSum() << "----------" << std::endl;
//
//   framework.setScheduler(new Grasp(100, INTRA_SWAP, ALL_ITERATIONS, 4, false));
//   framework.runScheduler();
//   framework.computeTctSummatory();
//   std::cout << "\n----------Grasp-InterSwap-TCT: " << framework.getTctSum() << "----------" << std::endl;
//
//   framework.setScheduler(new Grasp(100, INTER_INSERT, ALL_ITERATIONS, 4, false));
//   framework.runScheduler();
//   framework.computeTctSummatory();
//   std::cout << "\n----------Grasp-InterInsert-TCT: " << framework.getTctSum() << "----------" << std::endl;
//
//   framework.setScheduler(new Gnvs(50, ALL_ITERATIONS, INTER_INSERT, 5, false));
//   framework.runScheduler();
//   framework.computeTctSummatory();
//   std::cout << "\n----------GNVS-TCT: " << framework.getTctSum() << "----------" << std::endl;
// }
///////////////////////////////////////////////////////////