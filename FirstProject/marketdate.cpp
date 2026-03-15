#include "marketdate.h"

MarketDate::MarketDate(QString d) : foodStaffAvailability(0), artisanStaffAvailability(0),
    totalStaffAvailability(0), bookedFoodVendors(2), bookedArtisanVendors(2), price(75)
{
    date = d;
}

bool MarketDate::addVendor(Vendor* v) {
    if (v->getCategory() == Food) {
        return addFoodVendor(v);
    } else if (v->getCategory() == Artisan) {
        return addArtisanVendor(v);
    }

    return false;
}

bool MarketDate::removeVendor(Vendor* v) {
    if (v->getCategory() == Food) {
        return removeFoodVendor(v);
    } else if (v->getCategory() == Artisan) {
        return removeArtisanVendor(v);
    }

    return false;
}

bool MarketDate::hasVendor(Vendor* v) {
    if (v->getCategory() == Food) {
        return hasFoodVendor(v);
    } else if (v->getCategory() == Artisan) {
        return hasArtisanVendor(v);
    }

    return false;
}

bool MarketDate::atVendorCapacity(int category) {
    if (category == Food) {
        return atFoodVendorCapacity();
    } else if (category == Artisan) {
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

int MarketDate::getAvailableSlots(int category) {
    if (category == Food) {
        int count = 0;
        for (Vendor* v : bookedFoodVendors.getBookedSlots()) {
            if (v == nullptr) count++;
        }
        return count;
    } else if (category == Artisan) {
        int count = 0;
        for (Vendor* v : bookedArtisanVendors.getBookedSlots()) {
            if (v == nullptr) count++;
        }
        return count;
    }
    return 0;
}

