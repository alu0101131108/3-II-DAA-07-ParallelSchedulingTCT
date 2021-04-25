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
    bool anxietyMode_;

    Environment interSwap(Environment *env);
    Environment intraSwap(Environment *env);
    Environment interInsert(Environment *env);
    Environment intraInsert(Environment *env);
    void constructive(Environment *env);
    void update(Environment *env);
    
  public:
    Grasp(int threadsNumber, int operationType, int candidatesNumber, bool anxietyMode);
    void run(Environment *env);
};


#endif // __GRASP_H__