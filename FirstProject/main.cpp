#include "mainwindow.h"
#include "user.h"
#include "storage.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    Storage storage;

    storage.loadData();

    auto vendors = storage.getVendors();

    for (auto& vendor : vendors) {
            vendor.print();
        }
    storage.getOrganizer().print();
    storage.getAdmin().print();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

/*
Food Vendors:
1. thebreadcompany
Food (0)
TheBreadCompany
Elfi Lutz
mail@thebreadcompany.com
6135587921
39 St Clair Avenue W, Toronto, ON, M6A 2T2

2. jiyoungwoo
Food (0)
Bubba Tea
Jiyoung Woo
info@bubbatea.ca
6138667357
21 Pharmacy Drive, Hintonville, ON, N4P 1R9

3. mattsoup
Matthiew's Soup Spot
Matthieau Parfait
matt_soup@gmail.com
6138540908
46 Old Lane, Hintonville, ON, L5T 7Y6

4. jamsdiego
Jams by Diego
Lauro Diego
jamsbydiego@gmail.com
5147294419
59 Rue Guy, Montreal, QC, H3H 2L5

Artisan Vendors:
1. poppyjules
Artisan (1)
Poppy's Earrings
Poppy Jules
poppys_earrings@outlook.com
6137628641
100 Wellington Street, Ottawa, ON, K1A 0A9

2. homemade98
Artisan (1)
Homemade Hintonville
Percy Nikolas
homemadehandmade@gmail.com
3437658998
75 Port Lane, Hintonville, ON, L3R 5Y7

3. chetana
Artisan (1)
Subcontinental Attire Handmade
Chetana Jai
contact@subcontinentalattire.ca
6139986780
10 Rideau Street, Ottawa, ON, K1N 9J7

4. yijunart
Artisan (1)
Yijun's Art
Yijun Ying
yijunart@hotmail.com
6139681138
342 Garden Parkway, Hintonville, ON, L4N 6Y3

Organizer:
1. boss

Admin:
1. admin

*/
