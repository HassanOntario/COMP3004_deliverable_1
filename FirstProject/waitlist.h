#ifndef WAITLIST_H
#define WAITLIST_H

#include <queue>
#include <vector>
#include <QString>

#include "vendor.h"

// A single FIFO waitlist for one category on one market week
class Waitlist {
    public:
        Waitlist();

        bool addVendor(Vendor* v);
        bool removeVendor(Vendor* v);
        bool hasVendor(Vendor* v) const;

        // Returns the vendor at the front of the queue (next in line), or nullptr
        Vendor* peekNext() const;

        // Removes and returns the vendor at the front of the queue
        Vendor* popNext();

        // Returns the 1-based position of the vendor in the queue, or -1 if not found
        int getPosition(Vendor* v) const;

        int getSize() const;
        bool isEmpty() const;

        // Get all vendors in queue order for display
        std::vector<Vendor*> getAllVendors() const;

    private:
        std::vector<Vendor*> queue; // Using vector for easy position lookup + removal
};

#endif // WAITLIST_H
