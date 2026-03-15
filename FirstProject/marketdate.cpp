#include "marketdate.h"

MarketDate::MarketDate(std::string d) : foodStaffAvailability(0), artisanStaffAvailability(0),
    totalStaffAvailability(0), bookedFoodVendors(2), bookedArtisanVendors(2), price(75)
{
    date = d;
}

bool MarketDate::addVendor(Vendor* v) {
    if (v->getCategory() == 0) {
        return addFoodVendor(v);
    } else if (v->getCategory() == 1) {
        return addFoodVendor(v);
    }

    return false;
}

bool MarketDate::removeVendor(Vendor* v) {
    if (v->getCategory() == 0) {
        return removeFoodVendor(v);
    } else if (v->getCategory() == 1) {
        return removeFoodVendor(v);
    }

    return false;
}

bool MarketDate::hasVendor(Vendor* v) {
    if (v->getCategory() == 0) {
        return hasFoodVendor(v);
    } else if (v->getCategory() == 1) {
        return hasFoodVendor(v);
    }

    return false;
}

bool MarketDate::atVendorCapacity(int category) {
    if (category == 0) {
        return atFoodVendorCapacity();
    } else if (category == 1) {
        return atArtisanVendorCapacity();
    }

    return false;
}

void MarketDate::setFoodStaffAvailability(int n) {
    foodStaffAvailability = n;
    totalStaffAvailability = foodStaffAvailability + artisanStaffAvailability;
}

void MarketDate::setArtisanStaffAvailability(int n) {
    artisanStaffAvailability = n;
    totalStaffAvailability = foodStaffAvailability + artisanStaffAvailability;
}

void MarketDate::setPrice(double p) {
    price = p;
}

int MarketDate::getBookingStatus() {
    if (atFoodVendorCapacity() && atArtisanVendorCapacity()) {
        bookingStatus = FULL;
    } else {
        bookingStatus = AVAILABLE;
    }

    return bookingStatus;
}

