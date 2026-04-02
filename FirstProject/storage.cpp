#include "storage.h"

Storage::Storage() : organizer(""), admin("") {
}

void Storage::loadData() {

    QSqlQuery query;

    qDebug() << "were here";
    query.exec(
        "SELECT username FROM users WHERE (role = 'administrator')"
    );

    if (query.next()) {
        admin = Admin(query.value("username").toString());
    }


    query.exec(
        "SELECT username FROM users WHERE (role = 'organizer')"
    );

    if (query.next()) {
        organizer = Organizer(query.value("username").toString());
    }


    query.exec(
        "SELECT users.username, vendors.vendor_type, "
        "vendors.business_name, vendors.owner_name, vendors.email_address, vendors.phone_number, vendors.mailing_address, "
        "vendors.licenseNum, vendors.businessExpirationDate, "
        "vendors.policyNum, vendors.insuranceProvider, vendors.insuranceExpirationDate, "
        "vendors.certNum, vendors.certExpirationDate FROM vendors JOIN users on vendors.user_id = users.user_id"
    );

    qDebug() << "now here";

    while (query.next()) {
        Vendor vendor = setVendor(query);

        vendors.push_back(std::move(vendor));
    }

    qDebug() << "all vendors successfully added";

    query.exec("SELECT market_date FROM market_schedule");

    while(query.next()) {
        MarketDate mD(query.value("market_date").toString());
        marketDates.push_back(mD);
    }


}

std::vector<MarketDate>& Storage::getMarketDates() {
    return marketDates;
}

const std::vector<Vendor>& Storage::getVendors() const {
    return vendors;
}

std::vector<Vendor>& Storage::getVendorsMutable() {
    return vendors;
}

const Organizer& Storage::getOrganizer() const {
    return organizer;
}

const Admin& Storage::getAdmin() const {
    return admin;
}

User* Storage::findUser(const QString& username) {
    for (auto& v : vendors) {
        if (v.getUsername() == username) {
            return &v;
        }
    }
    if (organizer.getUsername() == username) {
        return &organizer;
    }
    if (admin.getUsername() == username) {
        return &admin;
    }
    return nullptr;
}

Vendor* Storage::findVendor(const QString& username) {
    for (auto& v : vendors) {
        if (v.getUsername() == username) {
            return &v;
        }
    }
    return nullptr;
}

Vendor Storage::setVendor(QSqlQuery& q) {

   Vendor vendor(q.value("username").toString());
   qDebug() << "in setVendor()";

   qDebug() << ":" << q.value("username").toString();

   vendor.setCategory(q.value("vendor_type").toString() == "food" ? 0 : 1);

   vendor.setBusinessInfo(
       q.value("business_name").toString(),
       q.value("owner_name").toString(),
       q.value("email_address").toString(),
       q.value("phone_number").toLongLong(),
       q.value("mailing_address").toString()
   );

   vendor.setBusinessLicence(
       q.value("licenseNum").toInt(),
       q.value("businessExpirationDate").toString()
   );

   vendor.setLiabilityInsurance(
       q.value("policyNum").toLongLong(),
       q.value("insuranceProvider").toString(),
       q.value("insuranceExpirationDate").toString()
   );

   vendor.setFoodHandlerCert(
       q.value("certNum").toInt(),
       q.value("certExpirationDate").toString()
   );

   return vendor;
   }
