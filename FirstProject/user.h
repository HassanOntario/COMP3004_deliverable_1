#ifndef USER_H
#define USER_H

#include <iostream>
#include <QString>

enum UserType {
    VENDOR,
    ORGANIZER,
    ADMINISTRATOR
};

class User {
    public:
        User(QString username) : username(username) {};
        virtual ~User() {}

        QString getUsername() const;
        bool verifyUsername(QString inputValue);
        void print() const;

        // Polymorphic method — overridden by each subclass
        virtual UserType getUserType() const = 0;
        virtual QString getUserTypeString() const = 0;

    protected:
        QString username;
};

#endif // USER_H
