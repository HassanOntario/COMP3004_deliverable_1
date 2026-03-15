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

