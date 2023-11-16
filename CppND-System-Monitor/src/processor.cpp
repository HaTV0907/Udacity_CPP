#include "processor.h"
#include <string>
#include <vector>
#include "linux_parser.h"

using std::string;
using std::vector;

Processor::Processor() : currTotalTime(0.0), currIdleTime(0.0){};

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  vector<long> cpuVal = str2l(LinuxParser::CpuUtilization());
  // cpu time = user + nice + system + idle + iowait + irq + softirq + steal
  float totalTime =
      cpuVal[LinuxParser::kUser_] + cpuVal[LinuxParser::kNice_] + cpuVal[LinuxParser::kSystem_] + cpuVal[LinuxParser::kIdle_] +
      cpuVal[LinuxParser::kIOwait_] + cpuVal[LinuxParser::kIRQ_] + cpuVal[LinuxParser::kSoftIRQ_] + cpuVal[LinuxParser::kSteal_];
  // idle time = idle + iowait
  float idleTime = cpuVal[LinuxParser::kIdle_] + cpuVal[LinuxParser::kIOwait_];
  // update cpu usage
  float diffIdleTime = idleTime - currIdleTime;
  float diffTotalTime = totalTime - currTotalTime;
  float diffUsageTime = (diffTotalTime - diffIdleTime) / diffTotalTime;
  // save the total and idle times
  currIdleTime = idleTime;
  currTotalTime = totalTime;
  return diffUsageTime;
}

// convert the given string vector into a long vector
vector<long> Processor::str2l(vector<string> val) {
  vector<long> longVct{};
  for (int it = 0; it < (int)val.size(); it++) {
    try {
      longVct.push_back(std::stol(val[it]));
    } catch (const std::invalid_argument& arg) {
      longVct.push_back((long)0);
    }
  }
  return longVct;
}