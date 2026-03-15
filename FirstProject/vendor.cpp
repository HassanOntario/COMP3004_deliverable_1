#include "vendor.h"

Vendor::Vendor(std::string username) : User(username) {};

void Vendor::setCategory(int i) {
    if (i == 0) {
        vendorType = Food;
    } else if (i == 1) {
        vendorType = Artisan;
    }
}

// setters
void Vendor::setBusinessInfo(std::string n, std::string on, std::string ea, long pn, std::string ma) {
    businessInfo.name = n;
    businessInfo.ownerName = on;
    businessInfo.emailAddress = ea;
    businessInfo.phoneNumber = pn;
    businessInfo.mailingAddress = ma;
};

void Vendor::setBusinessLicence(int ln, std::string ed) {
    businessLicence.licenceNum = ln;
    businessLicence.expirationDate = ed;
};

void Vendor::setLiabilityInsurance(long pn, std::string ip, std::string ed) {
    liabilityInsurance.policyNum = pn;
    liabilityInsurance.insuranceProvider = ip;
    liabilityInsurance.expirationDate = ed;
};

void Vendor::setFoodHandlerCert(int cn, std::string ed) {
    foodHandlerCert.certNum = cn;
    foodHandlerCert.expirationDate = ed;
}

// getters
int Vendor::getCategory() {
    return vendorType;
}

BusinessInfo Vendor::getBusinessInfo() {
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

BusinessLicence Vendor::getBusinessLicence() {
    return businessLicence;
    /*
    std::cout << "Licence Number: " << businessLicence.licenceNum
              << "\nExpiration Date: " << businessLicence.expirationDate
              << std::endl;
    */
}

Insurance Vendor::getLiabilityInsurance() {
    return liabilityInsurance;
    /*
    std::cout << "Policy Number: " << liabilityInsurance.policyNum
              << "\nInsurance Provider: " << liabilityInsurance.insuranceProvider
              << "\nExpiration Date: " << liabilityInsurance.expirationDate
              << std::endl;
    */
}

Certification Vendor::getFoodHandlerCert() {
    return foodHandlerCert;
    /*
    if (foodHandlerCert.certNum) {
        std::cout << "Certificate Number: " << foodHandlerCert.certNum
                  << "\nExpirationDate: " << foodHandlerCert.expirationDate
                  << std::endl;
    }
    */
}
