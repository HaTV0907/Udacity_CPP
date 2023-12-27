 #include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

#ifndef SYSLOG_H
#define SYSLOG_H

#define PROGRAM_PATH	"/proc/self/exe"
#define TIME_FORMAT		"[%Y/%m/%d %H:%M:%S]"

class sysLog
{
public:
	sysLog();
	~sysLog();
	bool checkDirExistance(const std::string& dirPath);
	void save(const std::string& msg);
	void setPlayerName(const std::string& name);
	const std::string& getPlayerName() const ;
private:
	std::string _player;
};
#endif // SYSLOG_H