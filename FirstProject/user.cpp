#include "user.h"

bool User::verifyUsername(std::string inputValue) {
    if (inputValue == username) { return true; }
    return false;
}

void User::print() {
    std::cout << username << std::endl;
}
