#include "IntrusionDetection.h" // Includes the header file for the IntrusionDetection class, which declares its methods
#include <sys/ptrace.h> // Includes the system header for ptrace, used to monitor and control the execution of another process
#include <sys/wait.h> // Includes definitions for waiting on child processes
#include <unistd.h> // Includes system call definitions, like fork and pid_t
#include <iostream> // Includes the I/O stream library for console output

// Defines ORIG_RAX to be 15 if it's not already defined. This macro specifies the offset for accessing the system call number in x86_64 architectures.
// This ensures compatibility for syscall monitoring.
#define ORIG_RAX 15 

//purpose: the IntrusionDetection class monitors the system calls made by a process to detect potential anomalies or suspicious behavior.
//the `monitorProcess` function is designed to trace the system calls of a child process (specified by child_pid).
void IntrusionDetection::monitorProcess(pid_t child_pid) {
    int status; // Variable to store the status of the child process.

    //loop continuously while the child process is running.
    while (waitpid(child_pid, &status, 0) && !WIFEXITED(status)) {
        //waits for the child process state to change. Continues if the child has not exited.

        //uses ptrace to peek at the system call being invoked by the child process.
        long syscall = ptrace(PTRACE_PEEKUSER, child_pid, sizeof(long) * ORIG_RAX, 0);
        //`PTRACE_PEEKUSER`: Reads data from the child process's user-space registers.
        //`child_pid`: Specifies the process being monitored.
        //`sizeof(long) * ORIG_RAX`: Calculates the offset to retrieve the system call number.
        //if successful, the value returned is the system call number.

        //outputs the intercepted system call to the console.
        std::cout << "System call intercepted: " << syscall << std::endl;

        //allows the child process to continue executing until the next system call.
        ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
        //`PTRACE_SYSCALL`: traces the next system call of the child process, 
        //pausing execution again when the system call is entered or exited.
    }
    //loop exits when the child process terminates (`WIFEXITED(status)` becomes true).
}

