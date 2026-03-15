#ifndef DASHBOARDCONTROL_H
#define DASHBOARDCONTROL_H

#include "user.h"
#include "vendor.h"

class DashboardControl {
    public:
        DashboardControl(const Vendor* v = nullptr);

        // vendor info
        const Vendor* getVendor() const { return vendor; }
        int getCategory() const { return vendor->getCategory(); }
        BusinessInfo getBusinessInfo() const { return vendor->getBusinessInfo(); }
        BusinessLicence getBusinessLicence() const { return vendor->getBusinessLicence(); }
        Insurance getLiabilityInsurance() const { return vendor->getLiabilityInsurance(); }
        Certification getFoodHanderCert() const { return vendor->getFoodHandlerCert(); }

        // stall bookings



    private:
        const Vendor* vendor;
};

#endif // DASHBOARDCONTROL_H
