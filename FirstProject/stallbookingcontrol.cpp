#include "stallbookingcontrol.h"

StallBookingControl::StallBookingControl(BookingList* bl, WaitlistManager* wm) : bl(bl), wm(wm) {}

bool StallBookingControl::vendorHasBooking(Vendor* v) {
    std::vector<Booking*> vendorBookings = bl->getBookingsByVendor(v);
    return !vendorBookings.empty();
}

bool StallBookingControl::bookStall(Vendor* v, MarketDate* md) {
    // Business rule: vendors can book only one market stall date at a time
    if (vendorHasBooking(v)) {
        return false;
    }

    // Check if stall is at capacity for this vendor's category
    if (md->atVendorCapacity(v->getCategory())) {
        return false;
    }

    // Add vendor to the market date and create booking
    if (md->addVendor(v)) {
        Booking* b = new Booking(v, md);
        bl->addBooking(b);

        // If vendor was on waitlist for this date, remove them
        wm->removeFromWaitlist(v, md);

        // Add confirmation notification
        v->addNotification("Booking confirmed for " + md->getDate() + ".");
        return true;
    }

    return false;
}

bool StallBookingControl::cancelStallBooking(Vendor* v, MarketDate* md) {
    Booking* b = bl->findBooking(v, md);
    if (b) {
        Category cat = v->getCategory();
        md->removeVendor(v);
        bl->removeBooking(b);

        // Add cancellation confirmation
        v->addNotification("Booking cancelled for " + md->getDate() + ".");

        // Notify the next vendor on the waitlist for this category and date
        wm->notifyNextVendor(md, cat);

        return true;
    }

    return false;
}

bool StallBookingControl::joinWaitlist(Vendor* v, MarketDate* md) {
    // Can't join waitlist if vendor already has a booking
    if (vendorHasBooking(v)) {
        return false;
    }

    // Can't join waitlist if stall is still available (should book instead)
    if (!md->atVendorCapacity(v->getCategory())) {
        return false;
    }

    if (wm->addToWaitlist(v, md)) {
        int pos = wm->getPosition(v, md);
        v->addNotification("Added to waitlist for " + md->getDate() +
                           ". Queue position: " + QString::number(pos) + ".");
        return true;
    }
    return false;
}

bool StallBookingControl::leaveWaitlist(Vendor* v, MarketDate* md) {
    if (wm->removeFromWaitlist(v, md)) {
        v->addNotification("Removed from waitlist for " + md->getDate() + ".");
        return true;
    }
    return false;
}
