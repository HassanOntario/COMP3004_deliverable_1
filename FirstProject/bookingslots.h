#ifndef BOOKINGSLOTS_H
#define BOOKINGSLOTS_H

#include <vector>

#include "vendor.h"

class BookingSlots {
    public:
        BookingSlots(int size);

        bool addVendor(Vendor* v);
        bool removeVendor(Vendor* v);
        bool hasVendor(Vendor* v) const;
        bool atCapacity() const;
        const std::vector<Vendor*>& getBookedSlots() const;

    private:
        std::vector<Vendor*> bookingSlots;
};

#endif // BOOKINGSLOTS_H
