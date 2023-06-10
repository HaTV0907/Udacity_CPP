#include "process.h"
#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : processId(pid) {
  // initialize all values
  calculateCpuUsage();
  getCommand();
  getRam();
  getUptime();
  getUser();
}

// this process's ID
int Process::Pid() {
  return processId;
}

// this process's CPU utilization
float Process::CpuUtilization() const {
  return cpuUsage;
}

// Return the command that generated this process
string Process::Command() {
  return command;
}

// Return this process's memory utilization
string Process::Ram() {
  return ram;
}

// Return the user (name) that generated this process
string Process::User() {
  return user;
}

// Return the age of this process (in seconds)
long int Process::UpTime() {
  return uptime;
}

// calculate the CPU utilization of this process and save in cpuUsage
void Process::calculateCpuUsage() {
  long uptime = 0;
  vector<float> val;
  float totaltime = 0;
  float seconds = 0;
  uptime = LinuxParser::UpTime();
  val = LinuxParser::CpuUtilization(Pid());
  if (val.size() == 5) {
    totaltime = val[UtimeS] + val[StimeS] + val[CutimeS] + val[CstimeS];
    seconds = uptime - val[StarttimeS];
    cpuUsage = totaltime / seconds;
  } else {
    cpuUsage = 0;
  }
}

void Process::getUser() {
  user = LinuxParser::User(Pid());
}

void Process::getCommand() {
  command = LinuxParser::Command(Pid());
}

void Process::getRam() {
  string val = LinuxParser::Ram(Pid());
  try {
    long conv = std::stol(val) / 1000;
    ram = std::to_string(conv);
  } catch (const std::invalid_argument& arg) {
    ram = "0";
  }
}

// get the running time of this process and save in uptime
void Process::getUptime() {
  uptime = LinuxParser::UpTime(Pid());
}