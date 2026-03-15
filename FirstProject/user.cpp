#include "user.h"
#include <QDebug>

bool User::verifyUsername(QString inputValue) {
    if (inputValue == username) { return true; }
    return false;
}

void User::print() const {
    qDebug() << username;
}

QString User::getUsername() const {
    return username;
}
