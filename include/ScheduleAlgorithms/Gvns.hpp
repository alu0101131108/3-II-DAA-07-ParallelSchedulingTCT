#ifndef __GNVS_H__
#define __GNVS_H__
#include "ScheduleAlgorithm.hpp"
#include "Grasp.hpp"
#include <vector>
#include <algorithm>

class Gnvs : public ScheduleAlgorithm
{
  private:
    int iterations_;
    int iterationsType_;
    int operationType_;
    int kMax_;
    bool anxiousMode_;
    
  public:
    Gnvs(int iterations, int iterationsType, int operationType,
        int kMax = 5, int anxiousMode = false);
    void run(Environment *env);
};


#endif // __GNVS_H__