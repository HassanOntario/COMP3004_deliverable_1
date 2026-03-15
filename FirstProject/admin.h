#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

class Admin : public User {
    public:
        Admin(QString username);

        // Polymorphic overrides
        UserType getUserType() const override { return ADMINISTRATOR; }
        QString getUserTypeString() const override { return "System Administrator"; }
};

#endif // ADMIN_H
