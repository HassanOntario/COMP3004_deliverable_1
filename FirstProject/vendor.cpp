#include "vendor.h"
#include "marketdate.h"

Vendor::Vendor(QString username) : User(username) {};

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
};

void Vendor::setBusinessLicence(int ln, QString ed) {
    businessLicence.licenceNum = ln;
    businessLicence.expirationDate = ed;
};

void Vendor::setLiabilityInsurance(long pn, QString ip, QString ed) {
    liabilityInsurance.policyNum = pn;
    liabilityInsurance.insuranceProvider = ip;
    liabilityInsurance.expirationDate = ed;
};

void Vendor::setFoodHandlerCert(int cn, QString ed) {
    foodHandlerCert.certNum = cn;
    foodHandlerCert.expirationDate = ed;
}

// getters
int Vendor::getCategory() const {
    return vendorType;
}

BusinessInfo Vendor::getBusinessInfo() const {
    return businessInfo;
    /*
    std::cout << "Business Name: " << businessInfo.name
              << "\nBusiness Owner: " << businessInfo.ownerName
              << "\nEmail Address: " << businessInfo.emailAddress
              << "\nPhone Number: " << businessInfo.phoneNumber
              << "\nMailing Address: " << businessInfo.mailingAddress
              << std::endl;
    */
}

BusinessLicence Vendor::getBusinessLicence() const {
    return businessLicence;
    /*
    std::cout << "Licence Number: " << businessLicence.licenceNum
              << "\nExpiration Date: " << businessLicence.expirationDate
              << std::endl;
    */
}

Insurance Vendor::getLiabilityInsurance() const {
    return liabilityInsurance;
    /*
    std::cout << "Policy Number: " << liabilityInsurance.policyNum
              << "\nInsurance Provider: " << liabilityInsurance.insuranceProvider
              << "\nExpiration Date: " << liabilityInsurance.expirationDate
              << std::endl;
    */
}

Certification Vendor::getFoodHandlerCert() const {
    return foodHandlerCert;
    /*
    if (foodHandlerCert.certNum) {
        std::cout << "Certificate Number: " << foodHandlerCert.certNum
                  << "\nExpirationDate: " << foodHandlerCert.expirationDate
                  << std::endl;
    }
    */
}

std::vector<MarketDate*> Vendor::getBookedDates() {
    return bookedDates;
}
