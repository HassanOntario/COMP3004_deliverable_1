QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    booking.cpp \
    bookinglist.cpp \
    bookingslots.cpp \
    dashboardcontrol.cpp \
    main.cpp \
    mainwindow.cpp \
    marketdate.cpp \
    organizer.cpp \
    stallbookingcontrol.cpp \
    user.cpp \
    vendor.cpp \
    storage.cpp

HEADERS += \
    admin.h \
    booking.h \
    bookinglist.h \
    bookingslots.h \
    dashboardcontrol.h \
    mainwindow.h \
    marketdate.h \
    organizer.h \
    stallbookingcontrol.h \
    user.h \
    vendor.h \
    storage.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
