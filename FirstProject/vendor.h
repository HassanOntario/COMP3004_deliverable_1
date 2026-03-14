#ifndef VENDOR_H
#define VENDOR_H

#include "user.h"

enum Category {
    Food,
    Artisan
};

struct BusinessInfo {
    std::string name;
    std::string ownerName;
    std::string emailAddress;
    int phoneNumber;
    std::string mailingAddress;
};

// expirationDate uses String for now, will use a more suitable data type when we need date functionality
struct BusinessLicence {
    int licenceNum;
    std::string expirationDate;
};

struct Insurance {
    int policyNum;
    std::string insuranceProvider;
    std::string expirationDate;
};

struct Certification {
    int certNum;
    std::string expirationDate;
};

class Vendor : public User {
    public:
        Vendor(std::string username);

        // setters
        void setCategory(int i);
        void setBusinessInfo(std::string n, std::string on, std::string ea, int pn, std::string ma);
        void setBusinessLicence(int ln, std::string ed);
        void setLiabilityInsurance(int pn, std::string ip, std::string ed);
        void setFoodHandlerCert(int cn, std::string ed);

        // getters
        int getCategory();
        void printBusinessInfo();
        void printBusinessLicence();
        void printLiabilityInsurance();
        void printFoodHandlerCert();

    private:
        enum Category vendorType; // 0 - Food, 1 - Artisan
        BusinessInfo businessInfo;
        BusinessLicence businessLicence;
        Insurance liabilityInsurance;
        Certification foodHandlerCert;
};

#endif // VENDOR_H
