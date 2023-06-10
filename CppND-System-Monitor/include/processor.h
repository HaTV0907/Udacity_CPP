#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
  float Utilization();
  Processor();

 private:
  // previous total cpu time since boot = user+nice+system+idle+iowait+irq+softirq+steal
  float prevTotalCpuTime;
  // previous idle time since boot = idle + iowait
  float prevIdleCpuTime;
  // auxiliary function
  vector<long> convertToLong(vector<string> values);
};

#endif