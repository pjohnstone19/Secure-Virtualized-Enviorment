#include "Authentication.h"
#include <openssl/sha.h>
#include <sstream>

std::string Authentication::hashPassword(const std::string &password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)password.c_str(), password.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << (int)hash[i];
    }
    return ss.str();
}

bool Authentication::authenticate(const std::string &inputPassword, const std::string &storedHash) {
    return hashPassword(inputPassword) == storedHash;
}
