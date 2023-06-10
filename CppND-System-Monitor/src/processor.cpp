#include "processor.h"
#include <string>
#include <vector>
#include "linux_parser.h"

using std::string;
using std::vector;

Processor::Processor() : prevTotalCpuTime(0.0), prevIdleCpuTime(0.0){};

// Return the aggregate CPU utilization
float Processor::Utilization() {
  vector<long> cpuValues;
  float totalCpuTime = 0.0;
  float idleCpuTime = 0.0;
  float diff = 0.0;
  // read current cpu values from file system
  cpuValues = convertToLong(LinuxParser::CpuUtilization());
  // total cpu time since boot = user + nice + system + idle + iowait + irq + softirq + steal
  totalCpuTime = cpuValues[LinuxParser::UserS] + cpuValues[LinuxParser::NiceS] + cpuValues[LinuxParser::SystemS] + cpuValues[LinuxParser::IdleS] +
                 cpuValues[LinuxParser::IOwaitS] + cpuValues[LinuxParser::IRQS] + cpuValues[LinuxParser::SoftIRQS] + cpuValues[LinuxParser::StealS];
  // idle time since boot = idle + iowait
  idleCpuTime = cpuValues[LinuxParser::IdleS] + cpuValues[LinuxParser::IOwaitS];

  // calculate the cpu usage
  diff = (totalCpuTime - prevTotalCpuTime) - (idleCpuTime - prevIdleCpuTime) / (totalCpuTime - prevTotalCpuTime);
  // update the total and idle times
  prevIdleCpuTime = idleCpuTime;
  prevTotalCpuTime = totalCpuTime;
  return diff;
}

vector<long> Processor::convertToLong(vector<string> values) {
  vector<long> convertedValues{};

  for (int it = 0; it < (int)values.size(); it++) {
    try {
      convertedValues.push_back(std::stol(values[it]));
    } catch (const std::invalid_argument& arg) {
      convertedValues.push_back((long)0);
    }
  }
  return convertedValues;
}