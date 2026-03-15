#ifndef USER_H
#define USER_H

#include <iostream>
#include <QString>

class User {
    public:
        User(QString username) : username(username) {};
        virtual ~User() {}

        QString getUsername() const;
        bool verifyUsername(QString inputValue);
        void print() const;

    protected:
        QString username;
};

#endif // USER_H
