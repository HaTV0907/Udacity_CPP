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

Process::Process(int pid) : pid(pid) {
    user = LinuxParser::User(Pid());
    cmd = LinuxParser::Command(Pid());
    uTime = LinuxParser::UpTime(Pid());
    // read values from filesystem
    long uptime = LinuxParser::UpTime();
    vector<float> val = LinuxParser::getCpuUtil(Pid());
    if (val.size() == 5) {
      float totaltime = val[uTimeT] + val[sTimeT] + val[cuTimeT] + val[csTimeT];
      float sec = uptime - val[startTimeT];
      cpuUtil = totaltime / sec;
    } else
      cpuUtil = 0;
    // processes memory utilization
    try {
      long conv = std::stol(LinuxParser::Ram(Pid())) / 1000;
      ram = std::to_string(conv);
    } catch (const std::invalid_argument& arg) {
      ram = "0";
    }
}
// TODO: Return this process's ID
int Process::Pid() { return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpuUtil; }

// TODO: Return the command that generated this process
string Process::Command() { return cmd; }

// TODO: Return this process's memory utilization
string Process::Ram() { return ram; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uTime; }
