#include "user.h"

bool User::verifyUsername(std::string inputValue) {
    if (inputValue == username) { return true; }
    return false;
}

void User::print() const {
    std::cout << username << std::endl;
}
