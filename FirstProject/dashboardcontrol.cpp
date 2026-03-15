#include "dashboardcontrol.h"

DashboardControl::DashboardControl(Vendor* v) : vendor(v) {}

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
