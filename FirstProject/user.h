#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
    public:
        User(std::string username) : username(username) {};
        virtual ~User() {}

        bool verifyUsername(std::string inputValue);
        void print() const;

    protected:
        std::string username;
};

#endif // USER_H
