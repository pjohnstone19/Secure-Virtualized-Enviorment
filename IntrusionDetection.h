#ifndef INTRUSIONDETECTION_H
#define INTRUSIONDETECTION_H

#include <sys/types.h>

class IntrusionDetection {
public:
    static void monitorProcess(pid_t child_pid);
};

#endif
