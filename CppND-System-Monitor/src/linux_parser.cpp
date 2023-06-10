#include "linux_parser.h"
#include <dirent.h>
#include <unistd.h>
#include <iostream>
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

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float memTotal = 0.0;
  float memFree = 0.0;
  string line;
  string name;
  string val;

// look for MemTotal and MemFree in /proc/meminfo
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      // remove ' kB' at the end, spaces and :
      // std::remove(line.begin(), line.end(), 'kB');
      std::remove(line.begin(), line.end(), ' ');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> name >> val) {
        // search for name memTotal
        if (name == "MemTotal") {
          memTotal = std::stof(val);
        }
        // search for name memFree
        else if (name == "MemFree") {
          memFree = std::stof(val);
          break;
        }
      }
    }
  }

  // Total used memory in percentage = (memTotal - MemFree) / memTotal
  return ((memTotal - memFree) / memTotal);
}

// Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  string time;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> time) {
        try {
          return std::stol(time);
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

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> cpuVals{};
  string line;
  string key;
  // refer the meaning of below variables in /proc/stat (https://man7.org/linux/man-pages/man5/proc.5.html)
  string user;
  string nice;
  string system;
  string idle;
  string iowait;
  string irq;
  string softirq;
  string steal;
  string guest;
  string guest_nice;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice) {
        if (key == "cpu") {
          cpuVals.push_back(user);
          cpuVals.push_back(nice);
          cpuVals.push_back(system);
          cpuVals.push_back(idle);
          cpuVals.push_back(iowait);
          cpuVals.push_back(irq);
          cpuVals.push_back(softirq);
          cpuVals.push_back(steal);
          cpuVals.push_back(guest);
          cpuVals.push_back(guest_nice);
          return cpuVals;
        }
      }
    }
  }
  return {};
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  string val;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> val) {
        if (key == "procs_running") {
            return std::stol(val);
        }
      }
    }
  }
  return 0;
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string val;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> val) {
        if (key == "processes") {
            return std::stol(val);
        }
      }
    }
  }
  return 0;
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string val = "";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, val);
    return val;
  }
  return val;
}

// Read the CPU usage of a process
// return the values in seconds
vector<float> LinuxParser::CpuUtilization(int pid) {
  vector<float> cpuVals{};
  string line;
  float time = 0;
  string val;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      for (int i = 1; i <= StarttimeS; i++) {
        linestream >> val;
        if (i == UtimeS || i == StimeS || i == CutimeS || i == CstimeS || i == StarttimeS) {
          time = std::stof(val) / sysconf(_SC_CLK_TCK);
          cpuVals.push_back(time);
        }
      }
    }
  }
  return cpuVals;
}

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
  string line;
  string key;
  string val = "";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> val) {
        if (key == "VmSize") {
          return val;
        }
      }
    }
  }
  return val;
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string line;
  string key;
  string val = "";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> val) {
        if (key == "Uid") {
          return val;
        }
      }
    }
  }
  return val;
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string uid;
  string line;
  string key;
  string val = "";
  string other;
  // find user name for this user in /etc/passwd
  uid = Uid(pid);
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> val >> other >> key) {
        if (key == uid) {
          return val;
        }
      }
    }
  }
  return val;
}

// Read and return the uptime of given pid
long LinuxParser::UpTime(int pid) {
  string line;
  long uptime = 0;
  string val;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      for (int i = 1; i <= StarttimeS; i++) {
        linestream >> val;
        if (i == StarttimeS) {
            uptime = std::stol(val) / sysconf(_SC_CLK_TCK);
            return uptime;
          }
        }
      }
    }
  return uptime;
}