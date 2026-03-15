#include "waitlistmanager.h"

WaitlistManager::WaitlistManager() {}

bool WaitlistManager::addToWaitlist(Vendor* v, MarketDate* md) {
    Category cat = v->getCategory();
    WaitlistKey key = {md, cat};
    return waitlists[key].addVendor(v);
}

bool WaitlistManager::removeFromWaitlist(Vendor* v, MarketDate* md) {
    Category cat = v->getCategory();
    WaitlistKey key = {md, cat};

    auto it = waitlists.find(key);
    if (it != waitlists.end()) {
        return it->second.removeVendor(v);
    }
    return false;
}

bool WaitlistManager::isOnWaitlist(Vendor* v, MarketDate* md) {
    Category cat = v->getCategory();
    WaitlistKey key = {md, cat};

    auto it = waitlists.find(key);
    if (it != waitlists.end()) {
        return it->second.hasVendor(v);
    }
    return false;
}

int WaitlistManager::getPosition(Vendor* v, MarketDate* md) {
    Category cat = v->getCategory();
    WaitlistKey key = {md, cat};

    auto it = waitlists.find(key);
    if (it != waitlists.end()) {
        return it->second.getPosition(v);
    }
    return -1;
}

Vendor* WaitlistManager::notifyNextVendor(MarketDate* md, Category category) {
    WaitlistKey key = {md, category};

    auto it = waitlists.find(key);
    if (it != waitlists.end() && !it->second.isEmpty()) {
        Vendor* nextVendor = it->second.peekNext();
        if (nextVendor) {
            QString msg = "A stall is now available for " + md->getDate() +
                          "! You are next in line. Please book your stall.";
            nextVendor->addNotification(msg);
        }
        return nextVendor;
    }
    return nullptr;
}

Waitlist* WaitlistManager::getWaitlist(MarketDate* md, Category category) {
    WaitlistKey key = {md, category};
    return &waitlists[key];
}

std::vector<WaitlistManager::WaitlistEntry> WaitlistManager::getVendorWaitlistEntries(Vendor* v) {
    std::vector<WaitlistEntry> entries;
    for (auto& pair : waitlists) {
        int pos = pair.second.getPosition(v);
        if (pos != -1) {
            WaitlistEntry entry;
            entry.marketDate = pair.first.marketDate;
            entry.category = pair.first.category;
            entry.position = pos;
            entries.push_back(entry);
        }
    }
    return entries;
}
