#ifndef STALLBOOKINGCONTROL_H
#define STALLBOOKINGCONTROL_H

#include "user.h"
#include "marketdate.h"
#include "bookinglist.h"
#include "waitlistmanager.h"

class StallBookingControl {
    public:
        StallBookingControl(BookingList* bl, WaitlistManager* wm);

        // Returns true on success. Enforces: max 2 per category, 1 booking per vendor.
        bool bookStall(Vendor* v, MarketDate* md);

        // Cancels booking, frees stall, notifies next waitlisted vendor
        bool cancelStallBooking(Vendor* v, MarketDate* md);

        // Check if vendor already has an active booking
        bool vendorHasBooking(Vendor* v);

        // Waitlist operations
        bool joinWaitlist(Vendor* v, MarketDate* md);
        bool leaveWaitlist(Vendor* v, MarketDate* md);

    private:
        BookingList* bl;
        WaitlistManager* wm;
};

#endif // STALLBOOKINGCONTROL_H
