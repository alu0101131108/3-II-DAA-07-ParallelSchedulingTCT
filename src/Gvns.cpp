#include "./../include/ScheduleAlgorithms/Gvns.hpp"

Gnvs::Gnvs(int iterations, int iterationsType, int graspOperation, int candidatesNumber, int anxiousMode) :
iterations_(iterations), iterationsType_(iterationsType), graspOperation_(graspOperation),
candidatesNumber_(candidatesNumber), anxiousMode_(anxiousMode)
{}

void Gnvs::run(Environment *env)
{
  int iterationsCount = 0;
  int minTctSum = UPPER_TIME_LIMIT;
  Environment winnerEnv = *env;
  bool noProgress;

  Grasp grasp(1, graspOperation_, iterationsType_, candidatesNumber_, anxiousMode_);
  int kIterator, lIterator;
  int lMax = 4, kMax = 4;

  Environment rvnsEnv, shakedEnv, vndEnv;
  std::vector<Machine> machines;
  std::vector<Task> originSchedule, destSchedule;
  int machineNumber, originScheduleSize, destScheduleSize;
  int mOrigin, mDest, tOrigin, tDest;

  while (iterationsCount < iterations_)
  {
    // Generate a solution, assuming there wont be progress.
    noProgress = true;
    rvnsEnv = *env;
    grasp.run(&rvnsEnv);
    rvnsEnv.computeTctSummatory();
    kIterator = 0;
    do
    {
      // Shake phase, 4 neighborhood structures generated with each operation are considered.
      // Randomly find 2 different machine indexes and 2 different scheduled task indexes.
      shakedEnv = rvnsEnv;
      machines = shakedEnv.getMachines();
      machineNumber = machines.size();
      mOrigin = rand() % machineNumber;
      mDest = (mOrigin + (rand() % machineNumber - 1) + 1) % machineNumber; 
      originSchedule = machines[mOrigin].getSchedule();
      destSchedule = machines[mDest].getSchedule();
      originScheduleSize = originSchedule.size();
      destScheduleSize = destSchedule.size();
      tOrigin = rand() % originScheduleSize;

      switch (kIterator)
      {
        case INTER_INSERT:
          tDest = rand() % destScheduleSize;
          shakedEnv.insertScheduledTasks(mOrigin, tOrigin, mDest, tDest);
          break;
        case INTRA_INSERT:
          tDest = (tOrigin + (rand() % originScheduleSize - 1) + 1) % originScheduleSize;
          shakedEnv.insertScheduledTasks(mOrigin, tOrigin, mOrigin, tDest);
          break;
        case INTER_SWAP:
          tDest = rand() % destScheduleSize;
          shakedEnv.swapScheduledTasks(mOrigin, tOrigin, mDest, tDest);
          break;
        case INTRA_SWAP:
          tDest = (tOrigin + (rand() % originScheduleSize - 1) + 1) % originScheduleSize;
          shakedEnv.swapScheduledTasks(mOrigin, tOrigin, mOrigin, tDest);
          break;
        default:
          std::cout << "ERROR: Unknown env operation in Gvns::run (K).\n";
          throw 140;
      }
      shakedEnv.computeTctSummatory();
      
      // VND phase.
      lIterator = 0;
      do 
      {
        vndEnv = shakedEnv;
        switch (lIterator)
        {
          case INTER_INSERT:
            grasp.interInsert(&vndEnv);
            break;
          case INTRA_INSERT:
            grasp.intraInsert(&vndEnv);
            break;
          case INTER_SWAP:
            grasp.interSwap(&vndEnv);
            break;
          case INTRA_SWAP:
            grasp.intraSwap(&vndEnv);
            break;
          default:
            std::cout << "ERROR: Unknown env operation in Gvns::run (L).\n";
            throw 140;
        }

        // VND Move or not phase.
        vndEnv.computeTctSummatory();
        if (vndEnv.getTctSum() < shakedEnv.getTctSum())
        {
          shakedEnv = vndEnv;
          lIterator = 1;
        }
        else
        {
          lIterator++;
        }
      } while (lIterator < lMax);

      // Move or not phase.
      if (vndEnv.getTctSum() < rvnsEnv.getTctSum())
      {
        rvnsEnv = vndEnv;
        kIterator = 1;
      }
      else
      {
        kIterator++;
      }
    } while (kIterator < kMax);

    // Keep trace of best solution found yet.
    if (rvnsEnv.getTctSum() < minTctSum)
    {
      minTctSum = rvnsEnv.getTctSum();
      winnerEnv = rvnsEnv;
      noProgress = false;
    }
    switch (iterationsType_)
    {
      case ALL_ITERATIONS:
        iterationsCount++;
        break;

      case NO_PROGRESS_ITERATIONS:
        if (noProgress)
          iterationsCount++;
        break;

      default:
        std::cout << "ERROR: Unknown iterations type in GVNS::run.\n";
        throw 73;
    }
  }
  env -> copy(&winnerEnv);
}
