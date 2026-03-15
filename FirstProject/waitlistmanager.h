#ifndef WAITLISTMANAGER_H
#define WAITLISTMANAGER_H

#include <map>
#include <QString>

#include "waitlist.h"
#include "vendor.h"
#include "marketdate.h"

// Key for identifying a specific waitlist: (market date pointer, category)
struct WaitlistKey {
    MarketDate* marketDate;
    Category category;

    bool operator<(const WaitlistKey& other) const {
        if (marketDate != other.marketDate) return marketDate < other.marketDate;
        return category < other.category;
    }
};

// Manages all waitlists — up to 8 (4 weeks × 2 categories)
// Implements Observer-like pattern: when a stall frees up, notifies next vendor
class WaitlistManager {
    public:
        WaitlistManager();

        // Add a vendor to the waitlist for a specific market date and their category
        bool addToWaitlist(Vendor* v, MarketDate* md);

        // Remove a vendor from the waitlist
        bool removeFromWaitlist(Vendor* v, MarketDate* md);

        // Check if vendor is on a waitlist for a specific date
        bool isOnWaitlist(Vendor* v, MarketDate* md);

        // Get position (1-based) of vendor on waitlist, -1 if not found
        int getPosition(Vendor* v, MarketDate* md);

        // Called when a stall becomes available — notifies the next vendor in queue
        // Returns the vendor that was notified, or nullptr if waitlist is empty
        Vendor* notifyNextVendor(MarketDate* md, Category category);

        // Get the waitlist for display purposes
        Waitlist* getWaitlist(MarketDate* md, Category category);

        // Get all waitlist entries for a specific vendor across all dates
        struct WaitlistEntry {
            MarketDate* marketDate;
            Category category;
            int position;
        };
        std::vector<WaitlistEntry> getVendorWaitlistEntries(Vendor* v);

    private:
        std::map<WaitlistKey, Waitlist> waitlists;
};

#endif // WAITLISTMANAGER_H
