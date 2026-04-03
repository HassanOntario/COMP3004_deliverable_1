#include "bookinglist.h"

BookingList::BookingList() {

}

bool BookingList::addBooking(Booking* b) {
    // Check for duplicate before adding
    if (std::find(bookings.begin(), bookings.end(), b) != bookings.end()) {
        return false;
    }
    bookings.push_back(b);
    return true;
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

std::vector<Booking*> BookingList::getBookingsByVendor(Vendor* v) {
    std::vector<Booking*> result;
    for (Booking* b : bookings) {
        if (b->getVendor() == v) {
            result.push_back(b);
        }
    }
    return result;
}

std::vector<Booking*> BookingList::getBookingsByMarketDate(MarketDate* md) {
    std::vector<Booking*> result;
    for (Booking* b : bookings) {
        if (b->getMarketDate() == md) {
            result.push_back(b);
        }
    }
    return result;
}
