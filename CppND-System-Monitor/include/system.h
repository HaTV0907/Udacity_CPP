#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  // the system's CPU
  Processor &Cpu();
  // a container composed of the system's processes are sorted by CPU usage
  std::vector<Process> &Processes();
  // the system's memory utilization
  float MemoryUtilization();
  // elapsed time in seconds since the system started running
  long UpTime();
  // the total number of processes in the system
  int TotalProcesses();
  // the number of processes running in the system
  int RunningProcesses();
  // the system's kernel identifier
  std::string Kernel();
  // the OS name
  std::string OperatingSystem();

 private:
  // the processor of the system
  Processor cpu = {};
  // container composed of the system's processes
  std::vector<Process> processes;
};

#endif