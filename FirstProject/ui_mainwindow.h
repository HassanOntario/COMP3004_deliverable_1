/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *loginScreen;
    QWidget *page;
    QFrame *frame_11;
    QFrame *frame_12;
    QLabel *label;
    QLineEdit *userInput;
    QPushButton *p1Button;
    QLabel *errorLabel;
    QLabel *label_2;
    QWidget *vendorPage;
    QLabel *vendorLabel;
    QWidget *orgPage;
    QLabel *orgLabel;
    QWidget *adminPage;
    QLabel *adminLabel;
    QWidget *vendorDashboard;
    QFrame *frame;
    QLabel *label_3;
    QFrame *frame_4;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *dashCategory;
    QLabel *dashEmail;
    QLabel *dashPhone;
    QLabel *dashAddress;
    QLabel *dashBusiness;
    QLabel *dashOwner;
    QFrame *frame_2;
    QFrame *frame_5;
    QFrame *frame_6;
    QListView *bookingsList;
    QLabel *label_8;
    QFrame *frame_7;
    QLabel *label_9;
    QFrame *frame_3;
    QFrame *frame_8;
    QFrame *frame_9;
    QListView *waitList;
    QLabel *label_10;
    QFrame *frame_10;
    QListView *listView;
    QLabel *label_11;
    QPushButton *returnLogin;
    QPushButton *vBrowse;
    QPushButton *vDash;
    QPushButton *vHome;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        loginScreen = new QStackedWidget(centralwidget);
        loginScreen->setObjectName(QString::fromUtf8("loginScreen"));
        loginScreen->setGeometry(QRect(0, 50, 801, 531));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        frame_11 = new QFrame(page);
        frame_11->setObjectName(QString::fromUtf8("frame_11"));
        frame_11->setGeometry(QRect(0, 0, 791, 501));
        frame_11->setFrameShape(QFrame::StyledPanel);
        frame_11->setFrameShadow(QFrame::Raised);
        frame_12 = new QFrame(frame_11);
        frame_12->setObjectName(QString::fromUtf8("frame_12"));
        frame_12->setGeometry(QRect(0, 40, 791, 461));
        frame_12->setFrameShape(QFrame::StyledPanel);
        frame_12->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame_12);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(178, 64, 121, 17));
        userInput = new QLineEdit(frame_12);
        userInput->setObjectName(QString::fromUtf8("userInput"));
        userInput->setGeometry(QRect(300, 60, 131, 25));
        p1Button = new QPushButton(frame_12);
        p1Button->setObjectName(QString::fromUtf8("p1Button"));
        p1Button->setGeometry(QRect(440, 60, 83, 25));
        errorLabel = new QLabel(frame_12);
        errorLabel->setObjectName(QString::fromUtf8("errorLabel"));
        errorLabel->setGeometry(QRect(250, 40, 241, 17));
        label_2 = new QLabel(frame_11);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(310, 10, 131, 31));
        loginScreen->addWidget(page);
        vendorPage = new QWidget();
        vendorPage->setObjectName(QString::fromUtf8("vendorPage"));
        vendorLabel = new QLabel(vendorPage);
        vendorLabel->setObjectName(QString::fromUtf8("vendorLabel"));
        vendorLabel->setGeometry(QRect(220, 110, 331, 17));
        loginScreen->addWidget(vendorPage);
        orgPage = new QWidget();
        orgPage->setObjectName(QString::fromUtf8("orgPage"));
        orgLabel = new QLabel(orgPage);
        orgLabel->setObjectName(QString::fromUtf8("orgLabel"));
        orgLabel->setGeometry(QRect(220, 110, 341, 17));
        loginScreen->addWidget(orgPage);
        adminPage = new QWidget();
        adminPage->setObjectName(QString::fromUtf8("adminPage"));
        adminLabel = new QLabel(adminPage);
        adminLabel->setObjectName(QString::fromUtf8("adminLabel"));
        adminLabel->setGeometry(QRect(230, 110, 351, 17));
        loginScreen->addWidget(adminPage);
        vendorDashboard = new QWidget();
        vendorDashboard->setObjectName(QString::fromUtf8("vendorDashboard"));
        frame = new QFrame(vendorDashboard);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 20, 231, 471));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(38, 10, 181, 20));
        frame_4 = new QFrame(frame);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(0, 40, 231, 431));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(frame_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 10, 211, 17));
        label_5 = new QLabel(frame_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 100, 211, 17));
        label_6 = new QLabel(frame_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 200, 211, 17));
        label_7 = new QLabel(frame_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 360, 211, 17));
        dashCategory = new QLabel(frame_4);
        dashCategory->setObjectName(QString::fromUtf8("dashCategory"));
        dashCategory->setGeometry(QRect(10, 380, 181, 17));
        dashEmail = new QLabel(frame_4);
        dashEmail->setObjectName(QString::fromUtf8("dashEmail"));
        dashEmail->setGeometry(QRect(10, 220, 211, 17));
        dashPhone = new QLabel(frame_4);
        dashPhone->setObjectName(QString::fromUtf8("dashPhone"));
        dashPhone->setGeometry(QRect(10, 240, 211, 17));
        dashAddress = new QLabel(frame_4);
        dashAddress->setObjectName(QString::fromUtf8("dashAddress"));
        dashAddress->setGeometry(QRect(10, 260, 211, 41));
        dashBusiness = new QLabel(frame_4);
        dashBusiness->setObjectName(QString::fromUtf8("dashBusiness"));
        dashBusiness->setGeometry(QRect(10, 30, 171, 17));
        dashOwner = new QLabel(frame_4);
        dashOwner->setObjectName(QString::fromUtf8("dashOwner"));
        dashOwner->setGeometry(QRect(10, 120, 211, 17));
        frame_4->raise();
        label_3->raise();
        frame_2 = new QFrame(vendorDashboard);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(240, 20, 531, 231));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_5 = new QFrame(frame_2);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(0, 0, 201, 231));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        frame_6 = new QFrame(frame_5);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setGeometry(QRect(0, 40, 201, 191));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        bookingsList = new QListView(frame_6);
        bookingsList->setObjectName(QString::fromUtf8("bookingsList"));
        bookingsList->setGeometry(QRect(0, 0, 201, 192));
        label_8 = new QLabel(frame_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(45, 12, 111, 17));
        frame_7 = new QFrame(frame_2);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setGeometry(QRect(200, 40, 331, 191));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(250, 10, 281, 20));
        frame_3 = new QFrame(vendorDashboard);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(240, 250, 531, 241));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        frame_8 = new QFrame(frame_3);
        frame_8->setObjectName(QString::fromUtf8("frame_8"));
        frame_8->setGeometry(QRect(0, 0, 261, 241));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        frame_9 = new QFrame(frame_8);
        frame_9->setObjectName(QString::fromUtf8("frame_9"));
        frame_9->setGeometry(QRect(0, 40, 261, 201));
        frame_9->setFrameShape(QFrame::StyledPanel);
        frame_9->setFrameShadow(QFrame::Raised);
        waitList = new QListView(frame_9);
        waitList->setObjectName(QString::fromUtf8("waitList"));
        waitList->setGeometry(QRect(0, 0, 261, 201));
        label_10 = new QLabel(frame_8);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(80, 10, 131, 17));
        frame_10 = new QFrame(frame_3);
        frame_10->setObjectName(QString::fromUtf8("frame_10"));
        frame_10->setGeometry(QRect(260, 40, 271, 201));
        frame_10->setFrameShape(QFrame::StyledPanel);
        frame_10->setFrameShadow(QFrame::Raised);
        listView = new QListView(frame_10);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(0, 0, 271, 201));
        label_11 = new QLabel(frame_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(330, 10, 191, 20));
        loginScreen->addWidget(vendorDashboard);
        returnLogin = new QPushButton(centralwidget);
        returnLogin->setObjectName(QString::fromUtf8("returnLogin"));
        returnLogin->setGeometry(QRect(10, 10, 83, 25));
        vBrowse = new QPushButton(centralwidget);
        vBrowse->setObjectName(QString::fromUtf8("vBrowse"));
        vBrowse->setGeometry(QRect(540, 10, 121, 25));
        vDash = new QPushButton(centralwidget);
        vDash->setObjectName(QString::fromUtf8("vDash"));
        vDash->setGeometry(QRect(670, 10, 83, 25));
        vHome = new QPushButton(centralwidget);
        vHome->setObjectName(QString::fromUtf8("vHome"));
        vHome->setGeometry(QRect(450, 10, 83, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        loginScreen->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "enter username:", nullptr));
        p1Button->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
        errorLabel->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "User Authentication", nullptr));
        vendorLabel->setText(QCoreApplication::translate("MainWindow", "welcome vendor,", nullptr));
        orgLabel->setText(QCoreApplication::translate("MainWindow", "welcome organizer,", nullptr));
        adminLabel->setText(QCoreApplication::translate("MainWindow", "welcome admin, ", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Business Information", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Business Name", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Owner Name", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Contact Information", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Vendor Category", nullptr));
        dashCategory->setText(QString());
        dashEmail->setText(QString());
        dashPhone->setText(QString());
        dashAddress->setText(QString());
        dashBusiness->setText(QString());
        dashOwner->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "Active Bookings", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Compliance Documentation Status", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Active Waitlist", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "System Notifications", nullptr));
        returnLogin->setText(QCoreApplication::translate("MainWindow", "<- login", nullptr));
        vBrowse->setText(QCoreApplication::translate("MainWindow", "Browse Market", nullptr));
        vDash->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        vHome->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
