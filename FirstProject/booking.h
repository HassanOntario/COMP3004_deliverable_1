#ifndef BOOKING_H
#define BOOKING_H

#include <QObject>

#include "user.h"
#include "marketdate.h"

class Booking
//       : public QObject
{
    // Q_OBJECT
    public:
        // explicit Booking(QObject *parent = nullptr);
        Booking(Vendor* v, MarketDate* md);

        // getters
        Vendor* getVendor();
        MarketDate* getMarketDate();

    private:
        Vendor* vendor;
        MarketDate* marketDate;

//  signals:

};

#endif // BOOKING_H
