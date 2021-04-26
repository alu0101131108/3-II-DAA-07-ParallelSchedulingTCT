#ifndef __GRASP_H__
#define __GRASP_H__
#include "ScheduleAlgorithm.hpp"
#include <vector>
#include <algorithm>

enum
{
  INTRA_INSERT,
  INTRA_SWAP,
  INTER_INSERT,
  INTER_SWAP
};

enum
{
  ALL_ITERATIONS,
  NO_PROGRESS_ITERATIONS
};

class Grasp : public ScheduleAlgorithm
{
  private:
    int threadsNumber_;
    int candidatesNumber_;
    int operationType_;
    int iterationsType_;
    bool anxiousMode_;

    void constructive(Environment *env);
    void update(Environment *env);
    
  public:
    Grasp(int threadsNumber, int operationType, int iterationsType, int candidatesNumber, bool anxiousMode = false);
    void run(Environment *env);
    void interSwap(Environment *env);
    void intraSwap(Environment *env);
    void interInsert(Environment *env);
    void intraInsert(Environment *env);
};


#endif // __GRASP_H__