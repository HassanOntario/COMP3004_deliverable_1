#include "booking.h"

/*
Booking::Booking(QObject *parent)
    : QObject{parent}
{

}
*/

Booking::Booking(Vendor* v, MarketDate* md) : vendor(v), marketDate(md) {}

Vendor* Booking::getVendor() { return vendor; }

MarketDate* Booking::getMarketDate() { return marketDate; }
