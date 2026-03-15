#ifndef DASHBOARDCONTROL_H
#define DASHBOARDCONTROL_H

#include "user.h"
#include "vendor.h"
#include "bookinglist.h"
#include "waitlistmanager.h"

class DashboardControl {
    public:
        DashboardControl(Vendor* v, BookingList* bl, WaitlistManager* wm);

        // vendor info — uses the stored vendor pointer
        Category getCategory() { return vendor->getCategory(); }
        BusinessInfo getBusinessInfo() { return vendor->getBusinessInfo(); }
        BusinessLicence getBusinessLicence() { return vendor->getBusinessLicence(); }
        Insurance getLiabilityInsurance() { return vendor->getLiabilityInsurance(); }
        Certification getFoodHandlerCert() { return vendor->getFoodHandlerCert(); }

        // stall bookings
        std::vector<Booking*> getActiveBookings();

        // waitlist entries
        std::vector<WaitlistManager::WaitlistEntry> getWaitlistEntries();

        // notifications
        std::vector<QString> getNotifications();
        void clearNotifications();

    private:
        Vendor* vendor;
        BookingList* bookingList;
        WaitlistManager* waitlistManager;
};

#endif // DASHBOARDCONTROL_H
