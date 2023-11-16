#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <sstream>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float memTotal, memFree;
  string line, key, val;
  // look for MemTotal and MemFree in /proc/meminfo
  std::ifstream memS(kProcDirectory + kMeminfoFilename);
  if (memS.is_open()) {
    while (std::getline(memS, line)) {
      std::remove(line.begin(), line.end(), ' ');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream lineS(line);
      while (lineS >> key >> val) {
        // look for MemTotal
        if ("MemTotal" == key) {
          memTotal = std::stof(val);
        }
        // look for memFree
        else if ("MemFree" == key) {
          memFree = std::stof(val);
          break;
        }
      }
    }
  }

  return ((memTotal - memFree) / memTotal);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line, uTime;
  std::ifstream uptimeS(kProcDirectory + kUptimeFilename);
  if (uptimeS.is_open()) {
    while (std::getline(uptimeS, line)) {
      std::istringstream lineS(line);
      while (lineS >> uTime) {
        try {
          return std::stol(uTime);
        } catch (const std::invalid_argument& arg) {
          return 0;
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> cpuUtils{};
  string line, key;
  string vuser{""};
  string vnice{""};
  string vsystem{""};
  string vidle{""};
  string viowait{""};
  string virq{""};
  string vsoftirq{""};
  string vsteal{""};
  string vguest{""};
  string vguest_nice{""};
  std::ifstream cpuUtilS(kProcDirectory + kStatFilename);
  if (cpuUtilS.is_open()) {
    while (std::getline(cpuUtilS, line)) {
      std::istringstream lineS(line);
      while (lineS >> key >> vuser >> vnice >> vsystem >> vidle >> viowait >> virq >> vsoftirq >> vsteal >> vguest >> vguest_nice) {
        if ("cpu" == key) {
          cpuUtils.push_back(vuser);
          cpuUtils.push_back(vnice);
          cpuUtils.push_back(vsystem);
          cpuUtils.push_back(vidle);
          cpuUtils.push_back(viowait);
          cpuUtils.push_back(virq);
          cpuUtils.push_back(vsoftirq);
          cpuUtils.push_back(vsteal);
          cpuUtils.push_back(vguest);
          cpuUtils.push_back(vguest_nice);
          break;
        }
      }
    }
  }
  return cpuUtils;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line, key, val;
  std::ifstream pS(kProcDirectory + kStatFilename);
  if (pS.is_open()) {
    while (std::getline(pS, line)) {
      std::istringstream lineS(line);
      while (lineS >> key >> val) {
        if ("processes" == key) {
          try {
            return std::stol(val);
          } catch (const std::invalid_argument& arg) {
            return 0;
          }
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line, key, val;
  std::ifstream statS(kProcDirectory + kStatFilename);
  if (statS.is_open()) {
    while (std::getline(statS, line)) {
      std::istringstream lineS(line);
      while (lineS >> key >> val) {
        if ("procs_running" == key) {
          try {
            return std::stol(val);
          } catch (const std::invalid_argument& arg) {
            return 0;
          }
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string val;
  std::ifstream pidS(kProcDirectory + "/" + std::to_string(pid) + kCmdlineFilename);
  if (pidS.is_open()) {
    std::getline(pidS, val);
    return val;
  }
  return val;
}


// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line, key, val;
  std::ifstream ramS(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if (ramS.is_open()) {
    while (std::getline(ramS, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream lineS(line);
      while (lineS >> key >> val) {
        if ("VmSize" == key) {
          return val;
        }
      }
    }
  }
  return val;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line, key, val;
  std::ifstream uidS(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if (uidS.is_open()) {
    while (std::getline(uidS, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream lineS(line);
      while (lineS >> key >> val) {
        if ("Uid" == key) {
          return val;
        }
      }
    }
  }
  return val;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string uid = Uid(pid);
  string line, key, val, other;
  std::ifstream userS(kPasswordPath);
  if (userS.is_open()) {
    while (std::getline(userS, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream lineS(line);
      while (lineS >> val >> other >> key) {
        if (uid == key) {
          return val;
        }
      }
    }
  }
  return val;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line, val;
  long uTime = 0;
  std::ifstream uTimeS(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if (uTimeS.is_open()) {
    while (std::getline(uTimeS, line)) {
      std::istringstream lineS(line);
      for (int i = 1; i <= startTimeT; i++) {
        lineS >> val;
        if (i == startTimeT) {
          try {
            uTime = std::stol(val) / sysconf(_SC_CLK_TCK);
            return uTime;
          } catch (const std::invalid_argument& arg) {
            return 0;
          }
        }
      }
    }
  }
  return uTime;
}

// get the CPU usage of a process in sec
vector<float> LinuxParser::getCpuUtil(int pid) {
  vector<float> cpuVals{};
  string line, val;
  float time;
  std::ifstream cpuUtilS(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if (cpuUtilS.is_open()) {
    while (std::getline(cpuUtilS, line)) {
      std::istringstream lineS(line);
      for (int i = 1; i <= startTimeT; i++) {
        lineS >> val;
        if (i == uTimeT || i == sTimeT || i == cuTimeT || i == csTimeT || i == startTimeT) {
          time = std::stof(val) / sysconf(_SC_CLK_TCK);
          cpuVals.push_back(time);
        }
      }
    }
  }
  return cpuVals;
}

