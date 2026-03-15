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

class Vendor : public User {
    public:
        Vendor(QString username);

        // Polymorphic overrides
        UserType getUserType() const override { return VENDOR; }
        QString getUserTypeString() const override { return "Vendor"; }

        // setters
        void setCategory(int i);
        void setBusinessInfo(QString n, QString on, QString ea, long pn, QString ma);
        void setBusinessLicence(int ln, QString ed);
        void setLiabilityInsurance(long pn, QString ip, QString ed);
        void setFoodHandlerCert(int cn, QString ed);

        // getters
        Category getCategory() const;
        BusinessInfo getBusinessInfo() const;
        BusinessLicence getBusinessLicence() const;
        Insurance getLiabilityInsurance() const;
        Certification getFoodHandlerCert() const;

        // notifications
        void addNotification(const QString& msg);
        std::vector<QString> getNotifications() const;
        void clearNotifications();

    private:
        Category vendorType;
        BusinessInfo businessInfo;
        BusinessLicence businessLicence;
        Insurance liabilityInsurance;
        Certification foodHandlerCert;
        std::vector<QString> notifications;
};

#endif // VENDOR_H
