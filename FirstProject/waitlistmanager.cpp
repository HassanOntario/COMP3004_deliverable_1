#include "waitlistmanager.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

WaitlistManager::WaitlistManager() {}

bool WaitlistManager::addToWaitlist(Vendor* v, MarketDate* md) {
    Category cat = v->getCategory();
    WaitlistKey key = {md, cat};
    if (!waitlists[key].addVendor(v)) {
        return false;
    }

    // Persist to database
    int pos = waitlists[key].getPosition(v);
    QSqlQuery q(DatabaseManager::instance().db());
    q.prepare("INSERT INTO waitlist (market_id, vendor_id, position) VALUES ("
              "(SELECT market_id FROM market_schedule WHERE market_date = :date), "
              "(SELECT vendor_id FROM vendors WHERE user_id = "
              "(SELECT user_id FROM users WHERE username = :uname)), :pos)");
    q.bindValue(":date", md->getDate());
    q.bindValue(":uname", v->getUsername());
    q.bindValue(":pos", pos);
    if (!q.exec()) {
        qWarning() << "DB INSERT waitlist failed:" << q.lastError().text();
    }

    return true;
}

bool WaitlistManager::removeFromWaitlist(Vendor* v, MarketDate* md) {
    Category cat = v->getCategory();
    WaitlistKey key = {md, cat};

    auto it = waitlists.find(key);
    if (it != waitlists.end()) {
        if (!it->second.removeVendor(v)) {
            return false;
        }

        // Remove from database
        QSqlQuery q(DatabaseManager::instance().db());
        q.prepare("DELETE FROM waitlist WHERE "
                  "market_id = (SELECT market_id FROM market_schedule WHERE market_date = :date) AND "
                  "vendor_id = (SELECT vendor_id FROM vendors WHERE user_id = "
                  "(SELECT user_id FROM users WHERE username = :uname))");
        q.bindValue(":date", md->getDate());
        q.bindValue(":uname", v->getUsername());
        if (!q.exec()) {
            qWarning() << "DB DELETE waitlist failed:" << q.lastError().text();
        }

        return true;
    }
    return false;
}

bool WaitlistManager::isOnWaitlist(Vendor* v, MarketDate* md) {
    Category cat = v->getCategory();
    WaitlistKey key = {md, cat};

    auto it = waitlists.find(key);
    if (it != waitlists.end()) {
        return it->second.hasVendor(v);
    }
    return false;
}

int WaitlistManager::getPosition(Vendor* v, MarketDate* md) {
    Category cat = v->getCategory();
    WaitlistKey key = {md, cat};

    auto it = waitlists.find(key);
    if (it != waitlists.end()) {
        return it->second.getPosition(v);
    }
    return -1;
}

Vendor* WaitlistManager::notifyNextVendor(MarketDate* md, Category category) {
    WaitlistKey key = {md, category};

    auto it = waitlists.find(key);
    if (it != waitlists.end() && !it->second.isEmpty()) {
        Vendor* nextVendor = it->second.popNext();
        if (nextVendor) {
            // Remove from database
            QSqlQuery q(DatabaseManager::instance().db());
            q.prepare("DELETE FROM waitlist WHERE "
                      "market_id = (SELECT market_id FROM market_schedule WHERE market_date = :date) AND "
                      "vendor_id = (SELECT vendor_id FROM vendors WHERE user_id = "
                      "(SELECT user_id FROM users WHERE username = :uname))");
            q.bindValue(":date", md->getDate());
            q.bindValue(":uname", nextVendor->getUsername());
            if (!q.exec()) {
                qWarning() << "DB DELETE waitlist (notify) failed:" << q.lastError().text();
            }

            QString msg = "A stall is now available for " + md->getDate() +
                          "! You are next in line. Please book your stall.";
            nextVendor->addNotification(msg);
        }
        return nextVendor;
    }
    return nullptr;
}

Waitlist* WaitlistManager::getWaitlist(MarketDate* md, Category category) {
    WaitlistKey key = {md, category};
    return &waitlists[key];
}

std::vector<WaitlistManager::WaitlistEntry> WaitlistManager::getVendorWaitlistEntries(Vendor* v) {
    std::vector<WaitlistEntry> entries;
    for (auto& pair : waitlists) {
        int pos = pair.second.getPosition(v);
        if (pos != -1) {
            WaitlistEntry entry;
            entry.marketDate = pair.first.marketDate;
            entry.category = pair.first.category;
            entry.position = pos;
            entries.push_back(entry);
        }
    }
    return entries;
}
