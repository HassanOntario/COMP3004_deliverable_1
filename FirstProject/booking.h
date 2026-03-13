#ifndef BOOKING_H
#define BOOKING_H

#include <QObject>

class booking : public QObject
{
    Q_OBJECT
public:
    explicit booking(QObject *parent = nullptr);

signals:

};

#endif // BOOKING_H
