#include "./../include/Environment.hpp"

Environment::Environment() : scheduler_(NULL) 
{}

Environment::~Environment() 
{}

std::vector<Task> const& Environment::getTasks() const
{
  return tasks_;
}

std::vector<Machine> const& Environment::getMachines() const
{
  return machines_;
}

Table const& Environment::getSetupTimes() const
{
  return setupTimes_;
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

void Environment::loadProblemFromFile(std::string filename) 
{
  try 
  {
    // Clear task and machine vectors.
    tasks_.clear();
    machines_.clear();

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
      tasks_.push_back(Task(tempTime));
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
  scheduler_ -> run(tasks_, machines_, setupTimes_);
}

void Environment::printTasks() 
{
  std::cout << "Task's process times" << std::endl;
  for (int i = 0; i < tasks_.size(); i++) 
  {
    std::cout << "[" << tasks_[i].getProcessTime() << "] ";
  }
  std::cout << std::endl;
}

void Environment::printMachineSchedules()
{
  std::vector<Task> schedules;
  for (int i = 0; i < machines_.size(); i++)
  {
    std::cout << "M" << i << "'s Schedule:" << std::endl;
    schedules = machines_[i].getSchedule();
    for (int j = 0; j < schedules.size(); j++)
    {
      std::cout << "[" << schedules[j].getProcessTime() << "] ";
    }
    std::cout << std::endl;
  }
}
