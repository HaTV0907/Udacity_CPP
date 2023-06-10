#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// Read and return the system memory utilization
float MemoryUtilization();
// Read and return the system uptime
long UpTime();
// Read and return the process IDs
std::vector<int> Pids();
// Read and return the total number of processes
int TotalProcesses();
// Read and return the number of running processes
int RunningProcesses();
// Read and return the name of the operating system
std::string OperatingSystem();
// Read and return the kernel of the system
std::string Kernel();

// CPU state enum
enum CPUStates {
  UserS = 0,
  NiceS,
  SystemS,
  IdleS,
  IOwaitS,
  IRQS,
  SoftIRQS,
  StealS,
  GuestS,
  GuestNiceS
};

// Read and return CPU utilization
std::vector<std::string> CpuUtilization();
long Jiffies();
long ActiveJiffies();
long ActiveJiffies(int pid);
long IdleJiffies();

// Read and return the CPU usage of a process in percent
std::vector<float> CpuUtilization(int pid);
// Read and return the command associated with a process
std::string Command(int pid);
// Read and return the memory used by a process in kB
std::string Ram(int pid);
// Read and return the user ID associated with a process
std::string Uid(int pid);
// Read and return the user associated with a process
std::string User(int pid);
// Read and return the uptime of a process
long int UpTime(int pid);
// CPU values of a process
enum ProcessCPUStates {
  UtimeS = 14,
  StimeS = 15,
  CutimeS = 16,
  CstimeS = 17,
  StarttimeS = 22
};

};  // end of LinuxParser namespace

#endif