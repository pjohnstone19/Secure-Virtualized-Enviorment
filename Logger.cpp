#include "Logger.h"
#include <fstream>
#include <iostream>

void Logger::logIncident(const std::string &message) {
    std::ofstream logFile("security.log", std::ios::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        std::cout << "Incident logged: " << message << std::endl;
    } else {
        std::cerr << "Failed to open log file." << std::endl;
    }
}
