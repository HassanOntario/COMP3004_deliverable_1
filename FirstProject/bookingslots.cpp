#include "bookingslots.h"

BookingSlots::BookingSlots(int size) : slots(size, nullptr) {}

bool BookingSlots::addVendor(Vendor* v) {}

bool BookingSlots::removeVendor(Vendor* v) {}

bool BookingSlots::hasVendor(Vendor* v) const {}

bool BookingSlots::atCapacity() const {}

const std::vector<Vendor*>& getBookedSlots() {}
