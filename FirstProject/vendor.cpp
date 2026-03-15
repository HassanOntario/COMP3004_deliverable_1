#include "vendor.h"
#include "marketdate.h"

Vendor::Vendor(QString username) : User(username), vendorType(Food) {};

void Vendor::setCategory(int i) {
    if (i == 0) {
        vendorType = Food;
    } else if (i == 1) {
        vendorType = Artisan;
    }
}

// setters
void Vendor::setBusinessInfo(QString n, QString on, QString ea, long pn, QString ma) {
    businessInfo.name = n;
    businessInfo.ownerName = on;
    businessInfo.emailAddress = ea;
    businessInfo.phoneNumber = pn;
    businessInfo.mailingAddress = ma;
}

void Vendor::setBusinessLicence(int ln, QString ed) {
    businessLicence.licenceNum = ln;
    businessLicence.expirationDate = ed;
}

void Vendor::setLiabilityInsurance(long pn, QString ip, QString ed) {
    liabilityInsurance.policyNum = pn;
    liabilityInsurance.insuranceProvider = ip;
    liabilityInsurance.expirationDate = ed;
}

void Vendor::setFoodHandlerCert(int cn, QString ed) {
    foodHandlerCert.certNum = cn;
    foodHandlerCert.expirationDate = ed;
}

// getters
Category Vendor::getCategory() const {
    return vendorType;
}

BusinessInfo Vendor::getBusinessInfo() const {
    return businessInfo;
}

BusinessLicence Vendor::getBusinessLicence() const {
    return businessLicence;
}

Insurance Vendor::getLiabilityInsurance() const {
    return liabilityInsurance;
}

Certification Vendor::getFoodHandlerCert() const {
    return foodHandlerCert;
}

// notifications
void Vendor::addNotification(const QString& msg) {
    notifications.push_back(msg);
}

std::vector<QString> Vendor::getNotifications() const {
    return notifications;
}

void Vendor::clearNotifications() {
    notifications.clear();
}

std::vector<MarketDate*> Vendor::getBookedDates() {
    return bookedDates;
}
