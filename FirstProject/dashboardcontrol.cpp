#include "dashboardcontrol.h"

DashboardControl::DashboardControl(Vendor* v, BookingList* bl, WaitlistManager* wm)
    : vendor(v), bookingList(bl), waitlistManager(wm) {}

std::vector<Booking*> DashboardControl::getActiveBookings() {
    return bookingList->getBookingsByVendor(vendor);
}

std::vector<WaitlistManager::WaitlistEntry> DashboardControl::getWaitlistEntries() {
    return waitlistManager->getVendorWaitlistEntries(vendor);
}

std::vector<QString> DashboardControl::getNotifications() {
    return vendor->getNotifications();
}

void DashboardControl::clearNotifications() {
    vendor->clearNotifications();
}

int DashboardControl::getCategory() { return vendor->getCategory(); }
BusinessInfo DashboardControl::getBusinessInfo() { return vendor->getBusinessInfo(); }
BusinessLicence DashboardControl::getBusinessLicence() { return vendor->getBusinessLicence(); }
Insurance DashboardControl::getLiabilityInsurance() { return vendor->getLiabilityInsurance(); }
Certification DashboardControl::getFoodHanderCert() { return vendor->getFoodHandlerCert(); }

bool DashboardControl::hasBookedDates() {
    if (!(vendor->getBookedDates().empty())) {
        return true;
    }

    return false;
}

std::vector<MarketDate*> DashboardControl::getBookedDates() {
    return vendor->getBookedDates();
}
