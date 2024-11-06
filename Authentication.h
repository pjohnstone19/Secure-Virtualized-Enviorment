#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>

class Authentication {
public:
    static std::string hashPassword(const std::string &password);
    static bool authenticate(const std::string &inputPassword, const std::string &storedHash);
};

#endif
