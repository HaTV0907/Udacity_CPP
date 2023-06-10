#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  // constructor to initialize Process with the read process-ID from filesystem
  Process(int pid);
  // this process's ID
  int Pid();
  // the user (name) that generated this process
  std::string User();
  // the command that generated this process
  std::string Command();
  // this process's CPU utilization in percent
  float CpuUtilization() const;
  // this process's memory utilization in MB
  std::string Ram();
  // the age of this process in seconds
  long int UpTime();

 private:
  // process-ID
  int processId;
  // user name that generated this process
  std::string user;
  // command that generated this process
  std::string command;
  // CPU usage of this process
  float cpuUsage;
  // processes memory utilization
  std::string ram;
  // age of this process
  long uptime;
  // CPU state
  enum ProcessCPUStates {
    UtimeS      = 0,
    StimeS      = 1,
    CutimeS     = 2,
    CstimeS     = 3,
    StarttimeS  = 4
  };

  void calculateCpuUsage();
  void getUser();
  void getCommand();
  void getRam();
  void getUptime();
};

#endif