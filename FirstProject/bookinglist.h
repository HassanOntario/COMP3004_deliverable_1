#ifndef BOOKINGLIST_H
#define BOOKINGLIST_H

#include <list>

#include "booking.h"

class BookingList {
    public:
        BookingList();

        bool addBooking(Booking* b);
        bool removeBooking(Booking* b);
        Booking* findBooking(Vendor* v, MarketDate* md);

        std::vector<Booking*> getBookingsByVendor(Vendor* v);
        std::vector<Booking*> getBookingsByMarketDate(MarketDate* md);

    private:
        std::vector<Booking*> bookings;
};

#endif // BOOKINGLIST_H
