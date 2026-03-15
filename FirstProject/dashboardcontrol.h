#ifndef DASHBOARDCONTROL_H
#define DASHBOARDCONTROL_H

#include "user.h"
#include "vendor.h"

class DashboardControl {
    public:
        DashboardControl(Vendor* v);

        // vendor info
        int getCategory();
        BusinessInfo getBusinessInfo();
        BusinessLicence getBusinessLicence();
        Insurance getLiabilityInsurance();
        Certification getFoodHanderCert();

        // stall bookings
        bool hasBookedDates();
        std::vector<MarketDate*> getBookedDates();

        // waitlists

        // confirmation messages

        // alerts

    private:
        Vendor* vendor;
};

#endif // DASHBOARDCONTROL_H
