#ifndef __ALTERNATIVEGREEDY_H__
#define __ALTERNATIVEGREEDY_H__
#include "ScheduleAlgorithm.hpp"
#include <vector>
#include <algorithm>

class AlternativeGreedy : public ScheduleAlgorithm
{
  void run(Environment *env);
};
#endif // __ALTERNATIVEGREEDY_H__