#include "Authentication.h" // Includes the header file for the Authentication class, which declares its methods
#include <openssl/sha.h> // Includes the OpenSSL library for hashing using the SHA256 algorithm
#include <sstream> // Includes the stringstream library for converting binary data to a hexadecimal string

//function to hash a password using SHA256
std::string Authentication::hashPassword(const std::string &password) {
    unsigned char hash[SHA256_DIGEST_LENGTH]; //declares an array to hold the SHA256 hash output
    SHA256((unsigned char *)password.c_str(), password.size(), hash); 
    //computes the SHA256 hash of the input password and stores it in the `hash` array

    std::stringstream ss; //creates a stringstream object to build the hexadecimal representation of the hash
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) { 
        ss << std::hex << (int)hash[i]; 
        //converts each byte of the hash into a hexadecimal string and appends it to the stringstream
    }
    return ss.str(); //returns the final hexadecimal string representation of the hashed password
}

//function to authenticate a user by comparing the hashed input password to the stored hash
bool Authentication::authenticate(const std::string &inputPassword, const std::string &storedHash) {
    return hashPassword(inputPassword) == storedHash; 
    //hashes the input password and checks if it matches the stored hash, returning true if they match
}
