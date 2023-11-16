#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
  Processor();
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  float currTotalTime;
  float currIdleTime;
  // convert vct string to vct long
  vector<long> str2l(vector<string> val);
};

#endif