#include "syslog.h"

sysLog::sysLog()
{
    _player = "Hatv";
}
sysLog::~sysLog()
{
    _player = "";
}


bool sysLog::checkDirExistance(const std::string& dirPath) {
    struct stat _temp;
    return (stat(dirPath.c_str(), &_temp) == 0 && S_ISDIR(_temp.st_mode));
}

void sysLog::setPlayerName(const std::string& name) {
    _player = name;
}

const std::string& sysLog::getPlayerName() const {
    return _player;
}

void sysLog::save(const std::string& msg) {
    char _temp[PATH_MAX];
    std::string _logDir{};
    ssize_t _strLen = readlink(PROGRAM_PATH, _temp, sizeof(_temp) - 1);

    if (_strLen != -1) {
        _temp[_strLen] = '\0';
        std::string programPath(_temp);
        size_t _slashIdx = programPath.rfind('/');
        if (_slashIdx != std::string::npos) {
            std::string _dir = programPath.substr(0, _slashIdx);
            _logDir = _dir + "/Log/";
            if (!checkDirExistance(_logDir)) {
                if (mkdir(_logDir.c_str(), 0777) == 0) {
                    std::cout << "Created new folder: " << _logDir << std::endl;
                }
                else {
                    std::cout << "New folder created failed." << std::endl;
                }
            }
        }
    }
    else {
        std::cout << "Cannot get program path" << std::endl;
    }

    std::ofstream _sysLogFile(_logDir + "/snakelog.txt", std::ios::app);


    if (_sysLogFile.is_open()) {

        time_t _presentTime = std::time(nullptr);
        char _timeBuff[80];
        strftime(_timeBuff, sizeof(_timeBuff), TIME_FORMAT, localtime(&_presentTime));
        _sysLogFile << _timeBuff << " " << msg << std::endl;
        _sysLogFile.close();
    }
    else {
        std::cout << "Can not Open " << _logDir << "snakelog.txt to write log." << std::endl;
    }
}
