#include "Logger.h" 
// includes the header file for the `Logger` class, which contains the declaration of the `logIncident` method.
#include <fstream> 
// includes the file stream library to enable file I/O operations, specifically for writing to the log file.
#include <iostream> 
// includes the I/O stream library to enable console output for feedback on the logging process.

void Logger::logIncident(const std::string &message) { 
    // defines the `logIncident` function, a static method of the `Logger` class.
    // it accepts a `std::string` message as input, which represents the incident to be logged.
    
    std::ofstream logFile("security.log", std::ios::app); 
    //creates an `std::ofstream` object to open the file "security.log" in append mode.
    // `std::ios::app` ensures that new log entries are added to the end of the file without overwriting existing content.
    
    if (logFile.is_open()) { 
        //checks if the log file was successfully opened.
        
        logFile << message << std::endl; 
        //writes the incident message to the log file followed by a newline character to separate entries.

        std::cout << "Incident logged: " << message << std::endl; 
        //outputs a confirmation message to the console, indicating that the incident was successfully logged.
    } else { 
        //executes this block if the log file could not be opened (e.g., due to permission issues or a missing file path).

        std::cerr << "Failed to open log file." << std::endl; 
        //outputs an error message to the standard error stream, indicating that logging failed.
    }
    //the function automatically closes the file when the `logFile` object goes out of scope, ensuring proper resource management.
}
