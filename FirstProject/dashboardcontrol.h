#ifndef DASHBOARDCONTROL_H
#define DASHBOARDCONTROL_H

#include "user.h"
#include "vendor.h"

class DashboardControl {
    public:
        DashboardControl(Vendor* v);

        // vendor info
        int getCategory(Vendor* v) { return v->getCategory(); }
        BusinessInfo getBusinessInfo(Vendor* v) { return v->getBusinessInfo(); }
        BusinessLicence getBusinessLicence(Vendor* v) { return v->getBusinessLicence(); }
        Insurance getLiabilityInsurance(Vendor* v) { return v->getLiabilityInsurance(); }
        Certification getFoodHanderCert(Vendor* v) { return v->getFoodHandlerCert(); }

        // stall bookings



    private:
        Vendor* vendor;
};

#endif // DASHBOARDCONTROL_H
