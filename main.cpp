#include <iostream>
#include <unistd.h>
#include "Authentication.h"
#include "Sandbox.h"
#include "IntrusionDetection.h"
#include "Logger.h"

void executeSecureProcess() 
{
    Sandbox::applySandbox();

    pid_t pid = fork();
    if (pid == 0) { // child process
        std::cout << "Executing secure process..." << std::endl;
        execlp("/bin/ls", "ls", nullptr); // example: sandboxed ls command
    } else if (pid > 0) { // parent process
        IntrusionDetection::monitorProcess(pid);
    } else {
        perror("Fork failed");
    }
}

int main() {
    std::string storedPasswordHash = Authentication::hashPassword("securepassword123");

    std::cout << "Enter password to access the system: ";
    std::string inputPassword;
    std::cin >> inputPassword;

    if (Authentication::authenticate(inputPassword, storedPasswordHash)) {
        std::cout << "Authentication successful." << std::endl;
        executeSecureProcess();
        Logger::logIncident("User successfully authenticated and executed a secure process.");
    } else {
        std::cerr << "Authentication failed!" << std::endl;
        Logger::logIncident("Failed authentication attempt.");
    }

    return 0;
}
