#include "format.h"

#include <string>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  string eTime = "00:00:00";
  long temp = 0;
  if (seconds > 0) {
    // get hours
    temp = seconds / 3600;
    eTime = int2str(temp);
    // get minutes
    temp = (seconds / 60) % 60;
    eTime += ":" + int2str(temp);
    // get seconds
    temp = seconds % 60;
    eTime += ":" + int2str(temp);
  }

  return eTime;
}
// convert long to string
std::string Format::int2str(long x) {
  return (x < 10) ? ("0" + std::to_string(x)) : std::to_string(x);
}