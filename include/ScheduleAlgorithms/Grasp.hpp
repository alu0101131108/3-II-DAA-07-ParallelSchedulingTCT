#ifndef __GRASP_H__
#define __GRASP_H__
#include "ScheduleAlgorithm.hpp"
#include <vector>
#include <algorithm>

class Grasp : public ScheduleAlgorithm
{
  private:
    int threadsNumber_;
    int candidatesNumber_;
    int operationType_;
    int iterationsType_;
    bool anxiousMode_;

    void interSwap(Environment *env);
    void intraSwap(Environment *env);
    void interInsert(Environment *env);
    void intraInsert(Environment *env);
    void constructive(Environment *env);
    void update(Environment *env);
    
  public:
    Grasp(int threadsNumber, int operationType, int iterationsType, int candidatesNumber, bool anxiousMode = false);
    void run(Environment *env);
};


#endif // __GRASP_H__