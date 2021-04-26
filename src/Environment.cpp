#include "./../include/Environment.hpp"

Environment::Environment() : scheduler_(NULL), tctSum_(0) 
{}

Environment::~Environment()
{}

const std::vector<Task>& Environment::getTasks() const
{
  return tasks_;
}

const std::vector<Machine>& Environment::getMachines() const
{
  return machines_;
}

const Table& Environment::getSetupTimes() const
{
  return setupTimes_;
}

const int Environment::getTctSum() const
{
  return tctSum_;
}

ScheduleAlgorithm* Environment::getSchedulerAlgorithm() const
{
  return scheduler_;
}

void Environment::setTasks(std::vector<Task> newTaskList) 
{
  tasks_ = newTaskList;
}

void Environment::setMachines(std::vector<Machine> newMachineList) 
{
  machines_ = newMachineList;
}

void Environment::setSetupTimes(Table newSetupTimes) 
{
  setupTimes_ = newSetupTimes;
}

void Environment::setScheduler(ScheduleAlgorithm *scheduleStrategy) 
{
  if (scheduler_ != NULL)
  {
    delete scheduler_;
  }
  scheduler_ = scheduleStrategy;
}

void Environment::setTctSum(int newTctSum) 
{
  tctSum_ = newTctSum;
}

void Environment::loadProblemFromFile(std::string filename) 
{
  try 
  {
    // Clear task and machine vectors.
    tasks_.clear();
    machines_.clear();
    tctSum_ = 0;

    // Variable declaration.
    int taskNumber, machineNumber, tempTime;
    std::string line;
    std::istringstream iss;
    std::ifstream ifs(filename);
    if (!ifs.is_open()) throw 10;

    // Read first two lines: number of tasks and machines.
    for (int i = 0; i < 2; i++) 
    {
      getline(ifs, line);
      line.erase(0, 2);
      iss.str(line);
      iss >> (i == 0 ? taskNumber : machineNumber);
      if (!iss) throw 20;
      iss.clear();
    }

    // Create machines.
    for (int i = 0; i < machineNumber; i++)
    {
      machines_.push_back(Machine());
    }

    // Read process times and create corresponding tasks. 
    getline(ifs, line);
    line.erase(0, line.find('\t'));
    iss.str(line);
    for (int i = 0; i < taskNumber; i++)
    {
      if (!(iss >> tempTime)) throw 30;
      tasks_.push_back(Task(i + 1, tempTime));
    }
    iss.clear();

    // Read setup times and fill table.
    getline(ifs, line);
    setupTimes_ = Table(taskNumber + 1, taskNumber + 1, 0);
    for (int i = 0; i < taskNumber + 1; i++)
    {
      getline(ifs, line);
      iss.str(line);
      for (int j = 0; j < taskNumber + 1; j++)
      {
        if (!(iss >> tempTime)) throw 40;
        setupTimes_.set(i, j, tempTime);
      }
      iss.clear();
    }
  }
  
  // Error handling.
  catch (int errn)
  {
    switch (errn) 
    {
      case 10:
        std::cout << "ERROR - Unable to open file: " << filename << std::endl;
        break;
      case 20:
        std::cout << "ERROR - Unable to read Task number or Machine number." << std::endl;
        break;
      case 30:
        std::cout << "ERROR - Unable to read Task's processing times." << std::endl;
        break;
      case 40:
        std::cout << "ERROR - Unable to read Task's setup times." << std::endl;
        break;
      default:
        std::cout << "ERROR - Unknown." << std::endl;
        break;
    }
    throw 100;
  }
}

void Environment::runScheduler() 
{
  if (scheduler_ != NULL)
  {
    for (int m = 0; m < machines_.size(); m++)
    {
      machines_[m].clearSchedule();
    }
    scheduler_->run(this);
  }
  else
  {
    std::cout << "ERROR: Scheduler Algorithm not attached to the environment.\n";
    throw 75;
  }
}

void Environment::printTasks() const 
{
  std::cout << "Task's process times" << std::endl;
  for (int i = 0; i < tasks_.size(); i++) 
  {
    if ((i + 1) % 6 == 0) std::cout << std::endl;
    tasks_[i].print();
    std::cout << " ";
  }
  std::cout << std::endl;
}

void Environment::printMachineSchedules() const
{
  std::vector<Task> schedules;
  for (int m = 0; m < machines_.size(); m++)
  {
    std::cout << "M" << m + 1 << "'s Schedule:" << std::endl;
    schedules = machines_[m].getSchedule();
    for (int t = 0; t < schedules.size(); t++)
    {
      if ((t + 1) % 11 == 0) std::cout << std::endl;
      std::cout << "[T" << schedules[t].getId() << "] ";
    }
    std::cout << std::endl;
  }
}

void Environment::copy(Environment *env)
{
  setupTimes_ = env->getSetupTimes();
  tasks_ = env->getTasks();
  machines_ = env->getMachines();
  tctSum_ = env->getTctSum();
}

void Environment::swapScheduledTasks(int mA, int tA, int mB, int tB)
{
  std::vector<Task> scheduleA = machines_[mA].getSchedule();
  std::vector<Task> scheduleB = machines_[mB].getSchedule();
  std::vector<Task>* pSchA = &scheduleA;
  std::vector<Task>* pSchB = (mA == mB) ? &scheduleA : &scheduleB;

  if (tA >= scheduleA.size() || tB >= scheduleB.size())
  {
    std::cout << "ERROR: Trying to access vector with out of range index.\n";
    throw 20;
  }

  Task tempTask = (*pSchA)[tA];
  (*pSchA)[tA] = (*pSchB)[tB];
  (*pSchB)[tB] = tempTask;

  machines_[mA].setSchedule(*pSchA);
  machines_[mB].setSchedule(*pSchB);
}

void Environment::insertScheduledTasks(int mOrigin, int tOrigin, int mDestination, int tDestination)
{
  std::vector<Task> scheduleOrigin = machines_[mOrigin].getSchedule();
  std::vector<Task> scheduleDest = machines_[mDestination].getSchedule();
  std::vector<Task>* origin = &scheduleOrigin;
  std::vector<Task>* destination = (mOrigin == mDestination) ? &scheduleOrigin : &scheduleDest;
  Task insertable = scheduleOrigin[tOrigin];

  origin -> erase(scheduleOrigin.begin() + tOrigin);
  if (tDestination >= destination->size())
  {
    destination -> push_back(insertable);
  }
  else
  {
    destination -> insert(destination -> begin() + tDestination, insertable);
  }

  machines_[mOrigin].setSchedule(*origin);
  machines_[mDestination].setSchedule(*destination);
}

void Environment::computeTctSummatory() 
{
  std::vector<Task> schedule;
  int previousTaskInd, machineTct, tctSum = 0;
  for (int m = 0; m < machines_.size(); m++)
  {
    schedule = machines_[m].getSchedule();
    machineTct = 0;
    for (int st = 0; st < schedule.size(); st++)
    {
      previousTaskInd = st == 0 ? 0 : schedule[st - 1].getId();
      machineTct += (setupTimes_.get(previousTaskInd, schedule[st].getId()) + schedule[st].getProcessTime()) * (schedule.size() - st);
    }
    tctSum += machineTct;
  }
  tctSum_ = tctSum;
}
