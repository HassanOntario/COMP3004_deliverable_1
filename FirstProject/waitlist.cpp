#include "waitlist.h"
#include <algorithm>

Waitlist::Waitlist() {}

bool Waitlist::addVendor(Vendor* v) {
    // Don't allow duplicates
    if (hasVendor(v)) {
        return false;
    }
    queue.push_back(v);
    return true;
}

bool Waitlist::removeVendor(Vendor* v) {
    auto it = std::find(queue.begin(), queue.end(), v);
    if (it != queue.end()) {
        queue.erase(it);
        return true;
    }
    return false;
}

bool Waitlist::hasVendor(Vendor* v) const {
    return std::find(queue.begin(), queue.end(), v) != queue.end();
}

Vendor* Waitlist::peekNext() const {
    if (queue.empty()) {
        return nullptr;
    }
    return queue.front();
}

Vendor* Waitlist::popNext() {
    if (queue.empty()) {
        return nullptr;
    }
    Vendor* v = queue.front();
    queue.erase(queue.begin());
    return v;
}

int Waitlist::getPosition(Vendor* v) const {
    for (size_t i = 0; i < queue.size(); ++i) {
        if (queue[i] == v) {
            return static_cast<int>(i) + 1; // 1-based
        }
    }
    return -1; // Not found
}

int Waitlist::getSize() const {
    return static_cast<int>(queue.size());
}

bool Waitlist::isEmpty() const {
    return queue.empty();
}

std::vector<Vendor*> Waitlist::getAllVendors() const {
    return queue;
}
