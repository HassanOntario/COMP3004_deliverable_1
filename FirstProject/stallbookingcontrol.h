#ifndef STALLBOOKINGCONTROL_H
#define STALLBOOKINGCONTROL_H

#include "user.h"
#include "marketdate.h"
#include "bookinglist.h"

class StallBookingControl {
    public:
        StallBookingControl(BookingList* bl);

        bool bookStall(Vendor* v, MarketDate* md);
        bool cancelStallBooking(Vendor* v, MarketDate* md);

    private:
        BookingList* bl;

};

#endif // STALLBOOKINGCONTROL_H
