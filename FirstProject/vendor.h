#ifndef VENDOR_H
#define VENDOR_H

#include "user.h"
#include <QString>
#include <vector>


enum Category {
    Food,
    Artisan
};

struct BusinessInfo {
    QString name;
    QString ownerName;
    QString emailAddress;
    long phoneNumber;
    QString mailingAddress;
};

// expirationDate uses String for now, will use a more suitable data type when we need date functionality
struct BusinessLicence {
    int licenceNum;
    QString expirationDate;
};

struct Insurance {
    long policyNum;
    QString insuranceProvider;
    QString expirationDate;
};

struct Certification {
    int certNum;
    QString expirationDate;
};

class MarketDate; // forward referencing to avoid circular dependency

class Vendor : public User {
    public:
        Vendor(QString username);

        // setters
        void setCategory(int i);
        void setBusinessInfo(QString n, QString on, QString ea, long pn, QString ma);
        void setBusinessLicence(int ln, QString ed);
        void setLiabilityInsurance(long pn, QString ip, QString ed);
        void setFoodHandlerCert(int cn, QString ed);

        // getters
        int getCategory() const;
        BusinessInfo getBusinessInfo() const;
        BusinessLicence getBusinessLicence() const;
        Insurance getLiabilityInsurance() const;
        Certification getFoodHandlerCert() const;

        std::vector<MarketDate*> getBookedDates();

    private:
        enum Category vendorType; // 0 - Food, 1 - Artisan
        BusinessInfo businessInfo;
        BusinessLicence businessLicence;
        Insurance liabilityInsurance;
        Certification foodHandlerCert;

        std::vector<MarketDate*> bookedDates;
};

#endif // VENDOR_H
