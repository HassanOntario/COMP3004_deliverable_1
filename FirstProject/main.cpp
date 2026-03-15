#include "mainwindow.h"
#include "user.h"
#include "storage.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    /*
    Storage storage;

    storage.loadData();

    auto vendors = storage.getVendors();

    for (auto& vendor : vendors) {
            vendor.print();
        }
    storage.getOrganizer().print();
    storage.getAdmin().print();
    */

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
