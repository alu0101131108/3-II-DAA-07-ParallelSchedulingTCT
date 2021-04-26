#include "./../include/ScheduleAlgorithms/Gvns.hpp"

Gnvs::Gnvs(int iterations, int iterationsType, int operationType, int kMax, int anxiousMode) :
iterations_(iterations), iterationsType_(iterationsType), operationType_(operationType),
kMax_(kMax), anxiousMode_(anxiousMode)
{}

void Gnvs::run(Environment *env)
{
  int iterationsCount = 0;
  int minTctSum = UPPER_TIME_LIMIT;
  Environment winnerEnv = *env;
  bool noProgress;

  Grasp grasp(10, operationType_, iterationsType_, 4, anxiousMode_);
  int kIterator, lIterator;
  int lMax = 4, kMax = kMax_;

  Environment initialEnv, shakedEnv, vndEnv;
  std::vector<Machine> machines;
  std::vector<Task> originSchedule, destSchedule;
  int machineNumber, originScheduleSize, destScheduleSize;
  int mOrigin, mDest, tOrigin, tDest;

  while (iterationsCount < iterations_)
  {
    // Generate a solution, assuming there wont be progress.
    noProgress = true;
    initialEnv = *env;
    grasp.run(&initialEnv);
    initialEnv.computeTctSummatory();
    kIterator = 1;
    do
    {
      // Shake phase. Random neighbour will be generated. Its distance will depend on kMax attr.
      // Randomly find 2 different machine indexes and 2 different scheduled task indexes.
      // Perform K times the operationType_ to shakeEnv in order to shake it.

      shakedEnv = initialEnv;
      for (int k = 0; k < kIterator; k++)
      {
        machines = shakedEnv.getMachines();
        machineNumber = machines.size();
        mOrigin = rand() % machineNumber;
        mDest = (mOrigin + (rand() % machineNumber - 1) + 1) % machineNumber; 
        originSchedule = machines[mOrigin].getSchedule();
        destSchedule = machines[mDest].getSchedule();
        tOrigin = rand() % originSchedule.size();

        switch (operationType_)
        {
          case INTER_INSERT:
            tDest = rand() % destSchedule.size();
            shakedEnv.insertScheduledTasks(mOrigin, tOrigin, mDest, tDest);
            break;
          case INTRA_INSERT:
            tDest = (tOrigin + (rand() % originSchedule.size() - 1) + 1) % originSchedule.size();
            shakedEnv.insertScheduledTasks(mOrigin, tOrigin, mOrigin, tDest);
            break;
          case INTER_SWAP:
            tDest = rand() % destSchedule.size();
            shakedEnv.swapScheduledTasks(mOrigin, tOrigin, mDest, tDest);
            break;
          case INTRA_SWAP:
            tDest = (tOrigin + (rand() % originSchedule.size() - 1) + 1) % originSchedule.size();
            shakedEnv.swapScheduledTasks(mOrigin, tOrigin, mOrigin, tDest);
            break;
          default:
            std::cout << "ERROR: Unknown env operation in Gvns::run (Shake).\n";
            throw 140;
        }
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
      if (vndEnv.getTctSum() < initialEnv.getTctSum())
      {
        initialEnv = vndEnv;
        kIterator = 1;
      }
      else
      {
        kIterator++;
      }
    } while (kIterator <= kMax);

    // Keep trace of best solution found yet.
    if (initialEnv.getTctSum() < minTctSum)
    {
      minTctSum = initialEnv.getTctSum();
      winnerEnv = initialEnv;
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
