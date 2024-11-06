#include "Sandbox.h"
#include <sys/prctl.h>
#include <iostream>
#include <cstdlib>

void Sandbox::applySandbox() {
    if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) {
        perror("Failed to enable no_new_privs");
        exit(1);
    }
    std::cout << "Sandbox applied: Process restricted from gaining new privileges." << std::endl;
}
