#ifndef __TASK_H__
#define __TASK_H__

const int UPPER_PT_LIMIT = 10000;

class Task
{
private:
  int processTime_;
public:
  Task(int processTime = 0);
  ~Task();
  void setProcessTime(int newTime);
  int getProcessTime() const;
};

#endif // __TASK_H__
