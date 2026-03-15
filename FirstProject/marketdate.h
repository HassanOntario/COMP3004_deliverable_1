#ifndef MARKETDATE_H
#define MARKETDATE_H

#include <string>

#include <bookingslots.h>

class MarketDate {
    public:
        MarketDate();

    private:
        std::string date;
        int totalStaffAvailability;
        int FoodStaffAvailability;
        int ArtisanStaffAvailability;
        BookingSlots bookedFoodVendors;
        BookingSlots bookedArtisanVendors;
        double price;
        int bookingStatus;
};

#endif // MARKETDATE_H
