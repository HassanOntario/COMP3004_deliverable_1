#include "mainwindow.h"
#include "user.h"
#include "storage.h"
#include "vendor.h"
#include "marketdate.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    /**
    Storage storage;

    storage.loadData();

    auto vendors = storage.getVendors();
    auto marketDates = storage.getMarketDates();

    for (auto& vendor : vendors) {
        vendor.print();
    }
    for (auto& date : marketDates) {
        std::cout << date.getPrice()  << "\n" <<  std::endl;
    }

    storage.getOrganizer().print();
    storage.getAdmin().print();
    */

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
