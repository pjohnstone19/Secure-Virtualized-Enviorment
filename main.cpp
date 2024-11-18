#include <iostream> // Includes the input/output stream library for handling console input and output
#include <unistd.h> // Includes POSIX API functions like fork() and execlp()
#include "Authentication.h" // Includes the header for the Authentication module
#include "Sandbox.h" // Includes the header for the Sandbox module
#include "IntrusionDetection.h" // Includes the header for the Intrusion Detection module
#include "Logger.h" // Includes the header for the Logger module

// function to execute a secure process after applying sandbox restrictions
void executeSecureProcess() 
{
    Sandbox::applySandbox(); // applies security restrictions using seccomp to sandbox the process

    pid_t pid = fork(); //creates a child process
    if (pid == 0) { // child process branch
        std::cout << "Executing secure process..." << std::endl; // outputs message to indicate execution
        execlp("/bin/ls", "ls", nullptr); // replaces the child process with the "ls" command
    } else if (pid > 0) { // parent process branch
        IntrusionDetection::monitorProcess(pid); // monitors the child process for suspicious activity
    } else { // error handling for fork failure
        perror("Fork failed"); // outputs an error message if fork() fails
    }
}

int main() {
    //simulates a stored hashed password in the system (this would typically come from a database)
    std::string storedPasswordHash = Authentication::hashPassword("securepassword123");

    std::cout << "Enter password to access the system: "; //prompts the user to enter a password
    std::string inputPassword; // declares a variable to store the user's input
    std::cin >> inputPassword; // reads the user input from the console

    // verifies if the input password matches the stored hash
    if (Authentication::authenticate(inputPassword, storedPasswordHash)) {
        std::cout << "Authentication successful." << std::endl; // outputs success message
        executeSecureProcess(); //calls the function to execute a secure process
        Logger::logIncident("User successfully authenticated and executed a secure process."); 
        // logs the successful authentication and secure process execution
    } else {
        std::cerr << "Authentication failed!" << std::endl; //outputs an error message for failed authentication
        Logger::logIncident("Failed authentication attempt."); 
        //logs the failed authentication attempt
    }
    return 0; //returns 0 to indicate successful program termination
}
