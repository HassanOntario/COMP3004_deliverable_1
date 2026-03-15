#include "storage.h"

Storage::Storage() : organizer("boss"), admin("admin") {
}

void Storage::loadData() {
    Vendor vendor1("thebreadcompany");
    vendor1.setCategory(0); // 0 = Food, 1 = Artisan
    vendor1.setBusinessInfo("The Bread Company", "Elfi Lutz", "mail@thebreadcompany.com", 6135587921, "39 St Clair Avenue W, Toronto, ON, M6A 2T2");
    vendor1.setBusinessLicence(493756908, "2030-06-30");
    vendor1.setLiabilityInsurance(109874567, "Algoma Mutual Insurance Company", "2030-06-30");
    vendor1.setFoodHandlerCert(475846, "2030-06-30");
    vendors.push_back(std::move(vendor1));

    Vendor vendor2("jiyoungwoo");
    vendor2.setCategory(0); // 0 = Food, 1 = Artisan
    vendor2.setBusinessInfo("Bubba Tea", "Jiyoung Woo", "info@bubbatea.ca", 6138667357, "21 Pharmacy Drive, Hintonville, ON, N4P 1R9");
    vendor2.setBusinessLicence(748755634, "2030-06-30");
    vendor2.setLiabilityInsurance(108564734, "Allstate Insurance Company", "2030-06-30");
    vendor2.setFoodHandlerCert(574835, "2030-06-30");
    vendors.push_back(std::move(vendor2));

    Vendor vendor3("mattsoup");
    vendor3.setCategory(0); // 0 = Food, 1 = Artisan
    vendor3.setBusinessInfo("Matthiew's Soup Spot", "Matthieau Parfait", "matt_soup@gmail.com", 6138540909, "46 Old Lane, Hintonville, ON, L5T 7Y6");
    vendor3.setBusinessLicence(584735287, "2030-06-30");
    vendor3.setLiabilityInsurance(100846385, "Echelon Insurance", "2030-06-30");
    vendor3.setFoodHandlerCert(746356, "2030-06-30");
    vendors.push_back(std::move(vendor3));

    Vendor vendor4("jamsdiego");
    vendor4.setCategory(0); // 0 = Food, 1 = Artisan
    vendor4.setBusinessInfo("Jams by Diego", "Lauro Diego", "jamsbydiego@gmail.com", 5147294419, "59 Rue Guy, Montreal, QC, H3H 2L5");
    vendor4.setBusinessLicence(539345664, "2030-06-30");
    vendor4.setLiabilityInsurance(107768535, "Allstate Insurance Company", "2030-06-30");
    vendor4.setFoodHandlerCert(305123, "2030-06-30");
    vendors.push_back(std::move(vendor4));

    Vendor vendor5("poppyjules");
    vendor5.setCategory(1); // 0 = Food, 1 = Artisan
    vendor5.setBusinessInfo("Poppy's Earrings", "Poppy Jules", "poppys_earrings@outlook.com", 6137628641, "100 Wellington Street, Ottawa, ON, K1A 0A9");
    vendor5.setBusinessLicence(985237121, "2030-06-30");
    vendor5.setLiabilityInsurance(102384203, "Reliance Insurance Company", "2030-06-30");
    vendor5.setFoodHandlerCert(320232, "2030-06-30");
    vendors.push_back(std::move(vendor5));

    Vendor vendor6("homemade98");
    vendor6.setCategory(1); // 0 = Food, 1 = Artisan
    vendor6.setBusinessInfo("Homemade Hintonville", "Percy Nikolas", "homemadehandmade@gmail.com", 3437658998, "75 Port Lane, Hintonville, ON, L3R 5Y7");
    vendor6.setBusinessLicence(232131214, "2030-06-30");
    vendor6.setLiabilityInsurance(101239112, "Westport Insurance Corporation", "2030-06-30");
    vendor6.setFoodHandlerCert(201933, "2030-06-30");
    vendors.push_back(std::move(vendor6));

    Vendor vendor7("chetana");
    vendor7.setCategory(1); // 0 = Food, 1 = Artisan
    vendor7.setBusinessInfo("Subcontinental Attire Homemade", "Chetana Jai", "contact@subcontinentalattire.ca", 6139986780, "10 Rideau Street, Ottawa, ON, K1N 9J7");
    vendor7.setBusinessLicence(101921123, "2030-06-30");
    vendor7.setLiabilityInsurance(100032325, "Westport Insurance Corporation", "2030-06-30");
    vendor7.setFoodHandlerCert(987332, "2030-06-30");
    vendors.push_back(std::move(vendor7));

    Vendor vendor8("yijunart");
    vendor8.setCategory(1); // 0 = Food, 1 = Artisan
    vendor8.setBusinessInfo("Yijun's Art", "Yijun Ying", "yijunart@hotmail.com", 6139681138, "342 Garden Parkway, Hintonville, ON, L4N 6Y3");
    vendor8.setBusinessLicence(342244536, "2030-06-30");
    vendor8.setLiabilityInsurance(107593443, "Westport Insurance Corporation", "2030-06-30");
    vendor8.setFoodHandlerCert(759322, "2030-06-30");
    vendors.push_back(std::move(vendor8));
}

const std::vector<Vendor>& Storage::getVendors() const {
    return vendors;
}

const Organizer& Storage::getOrganizer() const {
    return organizer;
}

const Admin& Storage::getAdmin() const {
    return admin;
}
