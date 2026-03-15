#include "bookinglist.h"

BookingList::BookingList() {

}

bool BookingList::addBooking(Booking* b) {
    bookings.push_back(b);
    if (std::find(bookings.begin(), bookings.end(), b) != bookings.end()) {
            return true;
        }

    return false;
}

bool BookingList::removeBooking(Booking* b) {
    auto it = std::find(bookings.begin(), bookings.end(), b);
    if (it != bookings.end()) {
        delete *it;
        bookings.erase(it);
        return true;
    }

    return false;
}

Booking* BookingList::findBooking(Vendor* v, MarketDate* md) {
    for (Booking* b : bookings) {
        if (b->getVendor() == v && b->getMarketDate() == md) {
            return b;
        }
    }

    return nullptr;
}
