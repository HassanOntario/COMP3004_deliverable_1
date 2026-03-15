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
        std::vector<Vendor>& getVendorsMutable();
        const Organizer& getOrganizer() const;
        const Admin& getAdmin() const;

        // Polymorphic user lookup — returns the User* matching the username, or nullptr
        User* findUser(const QString& username);
        Vendor* findVendor(const QString& username);

    private:
        std::vector<MarketDate> marketDates;
        std::vector<Vendor> vendors;
        Organizer organizer;
        Admin admin;
};

#endif // STORAGE_H
