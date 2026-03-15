#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "user.h"

class Organizer : public User {
    public:
        Organizer(QString username);

        // Polymorphic overrides
        UserType getUserType() const override { return ORGANIZER; }
        QString getUserTypeString() const override { return "Market Operator"; }
};

#endif // ORGANIZER_H
