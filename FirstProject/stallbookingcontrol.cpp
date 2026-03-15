#include "stallbookingcontrol.h"

StallBookingControl::StallBookingControl(BookingList* bl) : bl(bl) {}

bool StallBookingControl::bookStall(Vendor* v, MarketDate* md) {
    Booking* b = new Booking(v, md);
    if (bl->addBooking(b) && md->addVendor(v)) {
        return true;
    }

    return false; // Something went wrong
}

bool StallBookingControl::cancelStallBooking(Vendor* v, MarketDate* md) {
    Booking* b = bl->findBooking(v, md);
    if (b) {
        bl->removeBooking(b);
        return true;
    }

    return false; // Could not remove booking, or booking does not exist
}
