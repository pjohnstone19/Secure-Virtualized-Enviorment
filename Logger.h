#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    static void logIncident(const std::string &message);
};

#endif
