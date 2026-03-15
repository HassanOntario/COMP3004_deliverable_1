#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "user.h"
#include "vendor.h"
#include "organizer.h"
#include "admin.h"
#include "marketdate.h"

class Storage {
    public:
        Storage();

        void loadData();
        std::vector<MarketDate>& getMarketDates();
        const std::vector<Vendor>& getVendors() const;
        // std::vector<std::unique_ptr<User>> instead of std::vector<User*>
        // because we won't have to manually delete.
        // Keep in mind special behaviour with unique_ptr, e.g.,
        // it cannot be copied directly (to move, use std::move)
        const Organizer& getOrganizer() const;
        const Admin& getAdmin() const;

    private:
        std::vector<MarketDate> marketDates;
        std::vector<Vendor> vendors;
        Organizer organizer;
        Admin admin;
};

#endif // STORAGE_H
