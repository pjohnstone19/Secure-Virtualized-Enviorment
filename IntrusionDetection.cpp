#include "IntrusionDetection.h"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
//ORIG_RAX macro is architecture-specific. If it's not defined, you might be on 
//a non-x86 system (e.g., ARM). Replace ORIG_RAX with a proper register name. 
//this def assumes x86_64 architecture
#define ORIG_RAX 15

//IntrusionDetection: monitors system calls and logs anomalies.

void IntrusionDetection::monitorProcess(pid_t child_pid) {
    int status;
    while (waitpid(child_pid, &status, 0) && !WIFEXITED(status)) {
        long syscall = ptrace(PTRACE_PEEKUSER, child_pid, sizeof(long) * ORIG_RAX, 0);
        std::cout << "System call intercepted: " << syscall << std::endl;
        ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
    }
}
