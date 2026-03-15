#ifndef MARKETDATE_H
#define MARKETDATE_H

#include <QString>
#include <vector>

#include <bookingslots.h>

enum Status {
    FULL,
    AVAILABLE
};

class MarketDate {
    public:
        MarketDate(QString date);

        // booked vendors list modifications
        bool addVendor(Vendor* v);
        bool removeVendor(Vendor* v);
        bool hasVendor(Vendor* v);
        bool atVendorCapacity(int category);
        int getAvailableSlots(int category);

        // setters
        void setFoodStaffAvailability(int n);
        void setArtisanStaffAvailability(int n);
        void setPrice(double p);

        // getters
        QString getDate() const { return date; }
        int getFoodStaffAvailability() { return foodStaffAvailability; }
        int getArtisanStaffAvailability() { return artisanStaffAvailability; }
        int getTotalStaffAvailability() { return totalStaffAvailability; }
        const std::vector<Vendor*> getBookedFoodVendors() const { return bookedFoodVendors.getBookedSlots(); }
        const std::vector<Vendor*> getBookedArtisanVendors() const { return bookedArtisanVendors.getBookedSlots(); }
        int getPrice() { return price; }
        int getBookingStatus();

    private:
        bool addFoodVendor(Vendor* v) { return bookedFoodVendors.addVendor(v); }
        bool removeFoodVendor(Vendor* v) { return bookedFoodVendors.removeVendor(v); }
        bool hasFoodVendor(Vendor* v) const { return bookedFoodVendors.hasVendor(v); }
        bool atFoodVendorCapacity() const { return bookedFoodVendors.atCapacity(); }

        bool addArtisanVendor(Vendor* v) { return bookedArtisanVendors.addVendor(v); }
        bool removeArtisanVendor(Vendor* v) { return bookedArtisanVendors.removeVendor(v); }
        bool hasArtisanVendor(Vendor* v) const { return bookedArtisanVendors.hasVendor(v); }
        bool atArtisanVendorCapacity() const { return bookedArtisanVendors.atCapacity(); }

        QString date;
        int foodStaffAvailability;
        int artisanStaffAvailability;
        int totalStaffAvailability;
        BookingSlots bookedFoodVendors;
        BookingSlots bookedArtisanVendors;
        double price;
        enum Status bookingStatus;
};

#endif // MARKETDATE_H
