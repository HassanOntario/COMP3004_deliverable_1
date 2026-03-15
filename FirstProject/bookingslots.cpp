#include "bookingslots.h"
#include "vendor.h"

BookingSlots::BookingSlots(int size) : bookingSlots(size, nullptr) {}

bool BookingSlots::addVendor(Vendor* v) {
    for (Vendor*& slot : bookingSlots) {
        if (slot == nullptr) {
            slot = v;
            return true;
        }
    }

    return false;
}

bool BookingSlots::removeVendor(Vendor* v) {
    for (Vendor*& slot : bookingSlots) {
        if (slot == v) {
            slot = nullptr;
            return true;
        }
    }

    return false;
}

bool BookingSlots::hasVendor(Vendor* v) const {
    for (Vendor* slot : bookingSlots) {
        if (slot == v) {
            return true;
        }
    }

    return false;
}

bool BookingSlots::atCapacity() const {
    for (Vendor* slot : bookingSlots) {
        if (slot == nullptr) {
            return false;
        }
    }

    return true;
}

const std::vector<Vendor*>& BookingSlots::getBookedSlots() const { return bookingSlots; }
