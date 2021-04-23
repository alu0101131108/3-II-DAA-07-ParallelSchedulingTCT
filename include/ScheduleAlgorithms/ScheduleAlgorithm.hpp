#ifndef __SCHEDULEALGORITHM_H__
#define __SCHEDULEALGORITHM_H__
#include "./../Environment.hpp"

class Environment;
class ScheduleAlgorithm
{
public:
  virtual void run(Environment *env) = 0;
};

#endif // __SCHEDULEALGORITHM_H__