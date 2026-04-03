#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "storage.h"
#include "vendor.h"
#include "databasemanager.h"

#include <QString>
#include <QDebug>
#include <QHeaderView>
#include <QStringListModel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentVendor(nullptr)
    , marketBrowserPage(nullptr)
    , marketTable(nullptr)
    , operatorPage(nullptr)
    , opVendorCombo(nullptr)
    , opDateCombo(nullptr)
    , opStatusLabel(nullptr)
    , opInfoTable(nullptr)
{
    ui->setupUi(this);

    // Initialize the single database connection via DatabaseManager singleton
    if (!DatabaseManager::instance().initialize()) {
        qCritical() << "Failed to initialize database. Application may not function correctly.";
        return;
    }

    qDebug() << "Database connected successfully";

    storage.loadData();

    // Restore persisted bookings and waitlist entries from database
    loadBookingsFromDb();
    loadWaitlistFromDb();

    // Create control objects
    stallBookingControl = new StallBookingControl(&bookingList, &waitlistManager);

    // Build the market browser page programmatically and add to the stacked widget
    setupMarketBrowserPage();

    // Build the market operator page programmatically and add to the stacked widget
    setupOperatorPage();

    ui->returnLogin->hide();
    ui->vBrowse->hide();
    ui->vDash->hide();
    ui->vHome->hide();
}

MainWindow::~MainWindow()
{
    delete stallBookingControl;
    delete ui;
}

// ===================== LOGIN =====================

void MainWindow::on_p1Button_clicked() {

    QString username = ui->userInput->text().trimmed();

    if (username.isEmpty()) {
        ui->errorLabel->setText("Please enter a username.");
        return;
    }

    // Use polymorphic findUser for clean user-type routing
    User* user = storage.findUser(username);

    if (user == nullptr) {
        ui->errorLabel->setText("Please enter a valid username.");
        return;
    }

    // Use polymorphic getUserType() to route to correct interface
    switch (user->getUserType()) {
        case VENDOR: {
            currentVendor = static_cast<Vendor*>(user);
            ui->loginScreen->setCurrentWidget(ui->vendorPage);
            ui->vendorLabel->setText("Welcome, " + currentVendor->getBusinessInfo().name);

            ui->vBrowse->show();
            ui->vDash->show();
            ui->vHome->show();

            ui->vDash->setEnabled(true);
            ui->vBrowse->setEnabled(true);
            ui->vHome->setEnabled(false);
            break;
        }
        case ORGANIZER: {
            ui->loginScreen->setCurrentWidget(operatorPage);
            refreshOperatorStatus();
            break;
        }
        case ADMINISTRATOR: {
            ui->loginScreen->setCurrentWidget(ui->adminPage);
            ui->adminLabel->setText("Welcome Administrator, " + username);
            break;
        }
    }

    ui->returnLogin->show();
    ui->errorLabel->setText("");
}

// ===================== NAVIGATION =====================

void MainWindow::on_returnLogin_clicked() {
    ui->loginScreen->setCurrentWidget(ui->page);

    ui->returnLogin->hide();
    ui->vBrowse->hide();
    ui->vDash->hide();
    ui->vHome->hide();

    ui->userInput->setText("");
    ui->errorLabel->setText("");

    currentVendor = nullptr;
}

void MainWindow::on_vHome_clicked() {
    ui->loginScreen->setCurrentWidget(ui->vendorPage);

    ui->vDash->setEnabled(true);
    ui->vBrowse->setEnabled(true);
    ui->vHome->setEnabled(false);
}

void MainWindow::on_vDash_clicked() {
    ui->loginScreen->setCurrentWidget(ui->vendorDashboard);

    ui->vDash->setEnabled(false);
    ui->vBrowse->setEnabled(true);
    ui->vHome->setEnabled(true);

    populateDashboard();
}

void MainWindow::on_vBrowse_clicked() {
    ui->loginScreen->setCurrentWidget(marketBrowserPage);

    ui->vDash->setEnabled(true);
    ui->vBrowse->setEnabled(false);
    ui->vHome->setEnabled(true);

    populateMarketBrowser();
}

// ===================== DASHBOARD =====================

void MainWindow::populateDashboard() {
    if (!currentVendor) return;

    DashboardControl dashControl(currentVendor, &bookingList, &waitlistManager);

    // ---- BUSINESS INFORMATION ----
    BusinessInfo bInfo = dashControl.getBusinessInfo();
    ui->dashBusiness->setText(bInfo.name);
    ui->dashOwner->setText(bInfo.ownerName);
    ui->dashEmail->setText(bInfo.emailAddress);
    ui->dashPhone->setText(QString::number(bInfo.phoneNumber));
    ui->dashAddress->setText(bInfo.mailingAddress);

    if (dashControl.getCategory() == Food) {
        ui->dashCategory->setText("Food Vendor");
    } else {
        ui->dashCategory->setText("Artisan Vendor");
    }

    // ---- COMPLIANCE DOCUMENTATION STATUS ----
    // Find the compliance frame (frame_7) and populate it
    QFrame* complianceFrame = ui->vendorDashboard->findChild<QFrame*>("frame_7");
    if (complianceFrame) {
        // Clear existing widgets
        QLayout* existingLayout = complianceFrame->layout();
        if (existingLayout) {
            QLayoutItem* item;
            while ((item = existingLayout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
            delete existingLayout;
        }

        QVBoxLayout* compLayout = new QVBoxLayout(complianceFrame);
        compLayout->setSpacing(4);
        compLayout->setContentsMargins(8, 8, 8, 8);

        BusinessLicence bl = dashControl.getBusinessLicence();
        compLayout->addWidget(new QLabel("<b>Business Licence</b>"));
        compLayout->addWidget(new QLabel("Licence #: " + QString::number(bl.licenceNum)));
        compLayout->addWidget(new QLabel("Expires: " + bl.expirationDate));

        Insurance ins = dashControl.getLiabilityInsurance();
        compLayout->addWidget(new QLabel("<b>Liability Insurance</b>"));
        compLayout->addWidget(new QLabel("Policy #: " + QString::number(ins.policyNum)));
        compLayout->addWidget(new QLabel("Provider: " + ins.insuranceProvider));
        compLayout->addWidget(new QLabel("Expires: " + ins.expirationDate));

        if (dashControl.getCategory() == Food) {
            Certification cert = dashControl.getFoodHandlerCert();
            compLayout->addWidget(new QLabel("<b>Food Handler Certificate</b>"));
            compLayout->addWidget(new QLabel("Cert #: " + QString::number(cert.certNum)));
            compLayout->addWidget(new QLabel("Expires: " + cert.expirationDate));
        }

        compLayout->addStretch();
    }

    // ---- ACTIVE BOOKINGS ----
    QStringList bookingStrings;
    std::vector<Booking*> activeBookings = dashControl.getActiveBookings();
    for (Booking* b : activeBookings) {
        bookingStrings << b->getMarketDate()->getDate();
    }
    if (bookingStrings.empty()) {
        bookingStrings << "(No active bookings)";
    }
    QStringListModel* bookingsModel = new QStringListModel(bookingStrings, this);
    ui->bookingsList->setModel(bookingsModel);

    // ---- ACTIVE WAITLIST ----
    QStringList waitlistStrings;
    std::vector<WaitlistManager::WaitlistEntry> entries = dashControl.getWaitlistEntries();
    for (const auto& entry : entries) {
        QString line = entry.marketDate->getDate() +
                       " | Position: " + QString::number(entry.position);
        waitlistStrings << line;
    }
    if (waitlistStrings.empty()) {
        waitlistStrings << "(Not on any waitlists)";
    }
    QStringListModel* waitlistModel = new QStringListModel(waitlistStrings, this);
    ui->waitList->setModel(waitlistModel);

    // ---- SYSTEM NOTIFICATIONS ----
    QStringList notifStrings;
    std::vector<QString> notifications = dashControl.getNotifications();
    for (const QString& n : notifications) {
        notifStrings << n;
    }
    if (notifStrings.empty()) {
        notifStrings << "(No notifications)";
    }
    QStringListModel* notifModel = new QStringListModel(notifStrings, this);
    // The notifications list view (frame_10 area)
    QListView* notifList = ui->vendorDashboard->findChild<QListView*>("listView");
    if (notifList) {
        notifList->setModel(notifModel);
    }
}

// ===================== MARKET BROWSER =====================

void MainWindow::setupMarketBrowserPage() {
    marketBrowserPage = new QWidget();
    marketBrowserPage->setObjectName("marketBrowserPage");

    QVBoxLayout* mainLayout = new QVBoxLayout(marketBrowserPage);

    QLabel* title = new QLabel("<h2>Browse Available Market Dates</h2>");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    // Create market table
    marketTable = new QTableWidget(4, 6);
    marketTable->setHorizontalHeaderLabels({
        "Market Date", "Food Stalls\nAvailable", "Artisan Stalls\nAvailable",
        "Status", "Action", "Waitlist"
    });

    marketTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    marketTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    marketTable->setSelectionMode(QAbstractItemView::NoSelection);
    marketTable->verticalHeader()->setVisible(false);
    marketTable->setMinimumHeight(300);

    mainLayout->addWidget(marketTable);

    // Add to stacked widget
    ui->loginScreen->addWidget(marketBrowserPage);
}

void MainWindow::populateMarketBrowser() {
    if (!currentVendor || !marketTable) return;

    std::vector<MarketDate>& dates = storage.getMarketDates();
    marketTable->setRowCount(dates.size());

    for (int i = 0; i < (int)dates.size(); ++i) {
        MarketDate& md = dates[i];

        // Column 0: Date
        QTableWidgetItem* dateItem = new QTableWidgetItem(md.getDate());
        dateItem->setTextAlignment(Qt::AlignCenter);
        marketTable->setItem(i, 0, dateItem);

        // Column 1: Food stalls available
        int foodAvail = md.getAvailableSlots(Food);
        QTableWidgetItem* foodItem = new QTableWidgetItem(
            QString::number(foodAvail) + " / 2");
        foodItem->setTextAlignment(Qt::AlignCenter);
        marketTable->setItem(i, 1, foodItem);

        // Column 2: Artisan stalls available
        int artisanAvail = md.getAvailableSlots(Artisan);
        QTableWidgetItem* artisanItem = new QTableWidgetItem(
            QString::number(artisanAvail) + " / 2");
        artisanItem->setTextAlignment(Qt::AlignCenter);
        marketTable->setItem(i, 2, artisanItem);

        // Column 3: Status
        QString statusText;
        int vendorCat = currentVendor->getCategory();
        bool categoryFull = md.atVendorCapacity(vendorCat);
        bool vendorBooked = md.hasVendor(currentVendor);
        bool vendorOnWaitlist = waitlistManager.isOnWaitlist(currentVendor, &md);
        bool vendorHasAnyBooking = stallBookingControl->vendorHasBooking(currentVendor);

        if (vendorBooked) {
            statusText = "BOOKED";
        } else if (vendorOnWaitlist) {
            int pos = waitlistManager.getPosition(currentVendor, &md);
            statusText = "WAITLISTED (#" + QString::number(pos) + ")";
        } else if (categoryFull) {
            statusText = "FULL";
        } else {
            statusText = "AVAILABLE";
        }

        QTableWidgetItem* statusItem = new QTableWidgetItem(statusText);
        statusItem->setTextAlignment(Qt::AlignCenter);
        marketTable->setItem(i, 3, statusItem);

        // Column 4: Action button (Book / Cancel)
        QWidget* actionWidget = new QWidget();
        QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
        actionLayout->setContentsMargins(4, 2, 4, 2);

        if (vendorBooked) {
            QPushButton* cancelBtn = new QPushButton("Cancel Booking");
            cancelBtn->setStyleSheet("background-color: #e74c3c; color: white; padding: 4px 8px; border-radius: 3px;");
            int idx = i;
            connect(cancelBtn, &QPushButton::clicked, [this, idx]() {
                handleCancelBooking(idx);
            });
            actionLayout->addWidget(cancelBtn);
        } else if (!categoryFull && !vendorHasAnyBooking) {
            QPushButton* bookBtn = new QPushButton("Book Stall");
            bookBtn->setStyleSheet("background-color: #27ae60; color: white; padding: 4px 8px; border-radius: 3px;");
            int idx = i;
            connect(bookBtn, &QPushButton::clicked, [this, idx]() {
                handleBookStall(idx);
            });
            actionLayout->addWidget(bookBtn);
        } else if (vendorHasAnyBooking && !vendorBooked) {
            QLabel* lbl = new QLabel("Already booked\nanother date");
            lbl->setAlignment(Qt::AlignCenter);
            lbl->setStyleSheet("color: gray; font-size: 10px;");
            actionLayout->addWidget(lbl);
        } else {
            QLabel* lbl = new QLabel("-");
            lbl->setAlignment(Qt::AlignCenter);
            actionLayout->addWidget(lbl);
        }

        marketTable->setCellWidget(i, 4, actionWidget);

        // Column 5: Waitlist button
        QWidget* waitlistWidget = new QWidget();
        QHBoxLayout* waitlistLayout = new QHBoxLayout(waitlistWidget);
        waitlistLayout->setContentsMargins(4, 2, 4, 2);

        if (vendorOnWaitlist) {
            QPushButton* leaveBtn = new QPushButton("Leave Waitlist");
            leaveBtn->setStyleSheet("background-color: #e67e22; color: white; padding: 4px 8px; border-radius: 3px;");
            int idx = i;
            connect(leaveBtn, &QPushButton::clicked, [this, idx]() {
                handleLeaveWaitlist(idx);
            });
            waitlistLayout->addWidget(leaveBtn);
        } else if (categoryFull && !vendorBooked && !vendorHasAnyBooking) {
            QPushButton* joinBtn = new QPushButton("Join Waitlist");
            joinBtn->setStyleSheet("background-color: #3498db; color: white; padding: 4px 8px; border-radius: 3px;");
            int idx = i;
            connect(joinBtn, &QPushButton::clicked, [this, idx]() {
                handleJoinWaitlist(idx);
            });
            waitlistLayout->addWidget(joinBtn);
        } else {
            QLabel* lbl = new QLabel("-");
            lbl->setAlignment(Qt::AlignCenter);
            waitlistLayout->addWidget(lbl);
        }

        marketTable->setCellWidget(i, 5, waitlistWidget);
    }

    marketTable->resizeRowsToContents();
}

// ===================== BOOKING ACTIONS =====================

void MainWindow::handleBookStall(int marketIndex) {
    std::vector<MarketDate>& dates = storage.getMarketDates();
    if (marketIndex < 0 || marketIndex >= (int)dates.size()) return;

    MarketDate* md = &dates[marketIndex];

    if (stallBookingControl->bookStall(currentVendor, md)) {
        QMessageBox::information(this, "Booking Confirmed",
            "Your stall has been booked for " + md->getDate() + ".");
    } else {
        if (stallBookingControl->vendorHasBooking(currentVendor)) {
            QMessageBox::warning(this, "Booking Failed",
                "You already have an active booking. Vendors can only book one stall at a time.");
        } else {
            QMessageBox::warning(this, "Booking Failed",
                "No stalls available for your category on " + md->getDate() + ".\n"
                "You can join the waitlist instead.");
        }
    }

    refreshMarketBrowser();
}

void MainWindow::handleCancelBooking(int marketIndex) {
    std::vector<MarketDate>& dates = storage.getMarketDates();
    if (marketIndex < 0 || marketIndex >= (int)dates.size()) return;

    MarketDate* md = &dates[marketIndex];

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Cancellation",
        "Are you sure you want to cancel your booking for " + md->getDate() + "?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (stallBookingControl->cancelStallBooking(currentVendor, md)) {
            QMessageBox::information(this, "Booking Cancelled",
                "Your booking for " + md->getDate() + " has been cancelled.");
        } else {
            QMessageBox::warning(this, "Cancellation Failed",
                "Could not cancel the booking. Please try again.");
        }
    }

    refreshMarketBrowser();
}

void MainWindow::handleJoinWaitlist(int marketIndex) {
    std::vector<MarketDate>& dates = storage.getMarketDates();
    if (marketIndex < 0 || marketIndex >= (int)dates.size()) return;

    MarketDate* md = &dates[marketIndex];

    if (stallBookingControl->joinWaitlist(currentVendor, md)) {
        int pos = waitlistManager.getPosition(currentVendor, md);
        QMessageBox::information(this, "Waitlist Joined",
            "You have been added to the waitlist for " + md->getDate() +
            ".\nYour position: #" + QString::number(pos));
    } else {
        QMessageBox::warning(this, "Waitlist Failed",
            "Could not join the waitlist. Stalls may still be available, or you already have a booking.");
    }

    refreshMarketBrowser();
}

void MainWindow::handleLeaveWaitlist(int marketIndex) {
    std::vector<MarketDate>& dates = storage.getMarketDates();
    if (marketIndex < 0 || marketIndex >= (int)dates.size()) return;

    MarketDate* md = &dates[marketIndex];

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Leave Waitlist",
        "Are you sure you want to leave the waitlist for " + md->getDate() + "?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (stallBookingControl->leaveWaitlist(currentVendor, md)) {
            QMessageBox::information(this, "Waitlist Left",
                "You have been removed from the waitlist for " + md->getDate() + ".");
        } else {
            QMessageBox::warning(this, "Failed",
                "Could not remove you from the waitlist.");
        }
    }

    refreshMarketBrowser();
}

// ===================== MARKET OPERATOR =====================

void MainWindow::setupOperatorPage() {
    operatorPage = new QWidget();
    operatorPage->setObjectName("operatorPage");

    QVBoxLayout* mainLayout = new QVBoxLayout(operatorPage);
    mainLayout->setSpacing(12);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Title
    QLabel* title = new QLabel("<h2>Market Operator Dashboard</h2>");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    // --- Vendor selection ---
    QHBoxLayout* vendorRow = new QHBoxLayout();
    vendorRow->addWidget(new QLabel("Select Vendor:"));
    opVendorCombo = new QComboBox();
    const std::vector<Vendor>& vendors = storage.getVendors();
    for (const Vendor& v : vendors) {
        QString label = v.getUsername() + " (" + v.getBusinessInfo().name + " - " +
                        (v.getCategory() == Food ? "Food" : "Artisan") + ")";
        opVendorCombo->addItem(label, v.getUsername());
    }
    vendorRow->addWidget(opVendorCombo);
    mainLayout->addLayout(vendorRow);

    // --- Market date selection ---
    QHBoxLayout* dateRow = new QHBoxLayout();
    dateRow->addWidget(new QLabel("Select Market Date:"));
    opDateCombo = new QComboBox();
    std::vector<MarketDate>& dates = storage.getMarketDates();
    for (const MarketDate& md : dates) {
        opDateCombo->addItem(md.getDate());
    }
    dateRow->addWidget(opDateCombo);
    mainLayout->addLayout(dateRow);

    // --- Action buttons ---
    QHBoxLayout* btnRow = new QHBoxLayout();

    QPushButton* bookBtn = new QPushButton("Book Stall on Behalf");
    bookBtn->setStyleSheet("background-color: #27ae60; color: white; padding: 8px 16px; border-radius: 4px; font-weight: bold;");
    connect(bookBtn, &QPushButton::clicked, this, &MainWindow::handleOperatorBook);
    btnRow->addWidget(bookBtn);

    QPushButton* cancelBtn = new QPushButton("Cancel Booking on Behalf");
    cancelBtn->setStyleSheet("background-color: #e74c3c; color: white; padding: 8px 16px; border-radius: 4px; font-weight: bold;");
    connect(cancelBtn, &QPushButton::clicked, this, &MainWindow::handleOperatorCancel);
    btnRow->addWidget(cancelBtn);

    QPushButton* removeWlBtn = new QPushButton("Remove from Waitlist");
    removeWlBtn->setStyleSheet("background-color: #e67e22; color: white; padding: 8px 16px; border-radius: 4px; font-weight: bold;");
    connect(removeWlBtn, &QPushButton::clicked, this, &MainWindow::handleOperatorRemoveWaitlist);
    btnRow->addWidget(removeWlBtn);

    mainLayout->addLayout(btnRow);

    // --- Status label ---
    opStatusLabel = new QLabel("");
    opStatusLabel->setAlignment(Qt::AlignCenter);
    opStatusLabel->setWordWrap(true);
    opStatusLabel->setStyleSheet("font-size: 12px; padding: 8px;");
    mainLayout->addWidget(opStatusLabel);

    // --- Info table: show current bookings and waitlists per market date ---
    opInfoTable = new QTableWidget();
    opInfoTable->setColumnCount(5);
    opInfoTable->setHorizontalHeaderLabels({
        "Market Date", "Food Stalls\n(Booked/Max)", "Artisan Stalls\n(Booked/Max)",
        "Food Waitlist", "Artisan Waitlist"
    });
    opInfoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    opInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    opInfoTable->setSelectionMode(QAbstractItemView::NoSelection);
    opInfoTable->verticalHeader()->setVisible(false);
    mainLayout->addWidget(opInfoTable);

    mainLayout->addStretch();

    // Add to stacked widget
    ui->loginScreen->addWidget(operatorPage);
}

void MainWindow::refreshOperatorStatus() {
    if (!opInfoTable) return;

    std::vector<MarketDate>& dates = storage.getMarketDates();
    opInfoTable->setRowCount(dates.size());

    for (int i = 0; i < (int)dates.size(); ++i) {
        MarketDate& md = dates[i];

        // Date
        QTableWidgetItem* dateItem = new QTableWidgetItem(md.getDate());
        dateItem->setTextAlignment(Qt::AlignCenter);
        opInfoTable->setItem(i, 0, dateItem);

        // Food stalls booked
        int foodBooked = 2 - md.getAvailableSlots(Food);
        QTableWidgetItem* foodItem = new QTableWidgetItem(QString::number(foodBooked) + " / 2");
        foodItem->setTextAlignment(Qt::AlignCenter);
        opInfoTable->setItem(i, 1, foodItem);

        // Artisan stalls booked
        int artisanBooked = 2 - md.getAvailableSlots(Artisan);
        QTableWidgetItem* artisanItem = new QTableWidgetItem(QString::number(artisanBooked) + " / 2");
        artisanItem->setTextAlignment(Qt::AlignCenter);
        opInfoTable->setItem(i, 2, artisanItem);

        // Food waitlist
        Waitlist* foodWl = waitlistManager.getWaitlist(&md, Food);
        QString foodWlStr = foodWl->isEmpty() ? "(empty)" : QString::number(foodWl->getSize()) + " vendor(s)";
        QTableWidgetItem* foodWlItem = new QTableWidgetItem(foodWlStr);
        foodWlItem->setTextAlignment(Qt::AlignCenter);
        opInfoTable->setItem(i, 3, foodWlItem);

        // Artisan waitlist
        Waitlist* artisanWl = waitlistManager.getWaitlist(&md, Artisan);
        QString artisanWlStr = artisanWl->isEmpty() ? "(empty)" : QString::number(artisanWl->getSize()) + " vendor(s)";
        QTableWidgetItem* artisanWlItem = new QTableWidgetItem(artisanWlStr);
        artisanWlItem->setTextAlignment(Qt::AlignCenter);
        opInfoTable->setItem(i, 4, artisanWlItem);
    }

    opInfoTable->resizeRowsToContents();
}

void MainWindow::handleOperatorBook() {
    if (!opVendorCombo || !opDateCombo) return;

    QString vendorUsername = opVendorCombo->currentData().toString();
    QString dateStr = opDateCombo->currentText();

    Vendor* vendor = storage.findVendor(vendorUsername);
    if (!vendor) {
        opStatusLabel->setStyleSheet("color: red; font-size: 12px; padding: 8px;");
        opStatusLabel->setText("Error: Vendor not found.");
        return;
    }

    // Find market date
    MarketDate* md = nullptr;
    std::vector<MarketDate>& dates = storage.getMarketDates();
    for (auto& d : dates) {
        if (d.getDate() == dateStr) {
            md = &d;
            break;
        }
    }
    if (!md) {
        opStatusLabel->setStyleSheet("color: red; font-size: 12px; padding: 8px;");
        opStatusLabel->setText("Error: Market date not found.");
        return;
    }

    if (stallBookingControl->bookStall(vendor, md)) {
        opStatusLabel->setStyleSheet("color: green; font-size: 12px; padding: 8px;");
        opStatusLabel->setText("Success: Booked stall for " + vendor->getBusinessInfo().name +
                               " on " + dateStr + ".");
    } else {
        QString reason;
        if (stallBookingControl->vendorHasBooking(vendor)) {
            reason = "Vendor already has an active booking.";
        } else if (md->atVendorCapacity(vendor->getCategory())) {
            reason = "No stalls available for vendor's category on this date.";
        } else {
            reason = "Booking could not be completed.";
        }
        opStatusLabel->setStyleSheet("color: red; font-size: 12px; padding: 8px;");
        opStatusLabel->setText("Failed: " + reason);
    }

    refreshOperatorStatus();
}

void MainWindow::handleOperatorCancel() {
    if (!opVendorCombo || !opDateCombo) return;

    QString vendorUsername = opVendorCombo->currentData().toString();
    QString dateStr = opDateCombo->currentText();

    Vendor* vendor = storage.findVendor(vendorUsername);
    if (!vendor) {
        opStatusLabel->setStyleSheet("color: red; font-size: 12px; padding: 8px;");
        opStatusLabel->setText("Error: Vendor not found.");
        return;
    }

    MarketDate* md = nullptr;
    std::vector<MarketDate>& dates = storage.getMarketDates();
    for (auto& d : dates) {
        if (d.getDate() == dateStr) {
            md = &d;
            break;
        }
    }
    if (!md) {
        opStatusLabel->setStyleSheet("color: red; font-size: 12px; padding: 8px;");
        opStatusLabel->setText("Error: Market date not found.");
        return;
    }

    if (stallBookingControl->cancelStallBooking(vendor, md)) {
        opStatusLabel->setStyleSheet("color: green; font-size: 12px; padding: 8px;");
        opStatusLabel->setText("Success: Cancelled booking for " + vendor->getBusinessInfo().name +
                               " on " + dateStr + ".");
    } else {
        opStatusLabel->setStyleSheet("color: red; font-size: 12px; padding: 8px;");
        opStatusLabel->setText("Failed: Vendor does not have a booking on this date.");
    }

    refreshOperatorStatus();
}

void MainWindow::handleOperatorRemoveWaitlist() {
    if (!opVendorCombo || !opDateCombo) return;

    QString vendorUsername = opVendorCombo->currentData().toString();
    QString dateStr = opDateCombo->currentText();

    Vendor* vendor = storage.findVendor(vendorUsername);
    if (!vendor) {
        opStatusLabel->setStyleSheet("color: red; font-size: 12px; padding: 8px;");
        opStatusLabel->setText("Error: Vendor not found.");
        return;
    }

    MarketDate* md = nullptr;
    std::vector<MarketDate>& dates = storage.getMarketDates();
    for (auto& d : dates) {
        if (d.getDate() == dateStr) {
            md = &d;
            break;
        }
    }
    if (!md) {
        opStatusLabel->setStyleSheet("color: red; font-size: 12px; padding: 8px;");
        opStatusLabel->setText("Error: Market date not found.");
        return;
    }

    if (stallBookingControl->leaveWaitlist(vendor, md)) {
        opStatusLabel->setStyleSheet("color: green; font-size: 12px; padding: 8px;");
        opStatusLabel->setText("Success: Removed " + vendor->getBusinessInfo().name +
                               " from waitlist for " + dateStr + ".");
    } else {
        opStatusLabel->setStyleSheet("color: red; font-size: 12px; padding: 8px;");
        opStatusLabel->setText("Failed: Vendor is not on the waitlist for this date.");
    }

    refreshOperatorStatus();
}

// ===================== REFRESH HELPERS =====================

void MainWindow::refreshMarketBrowser() {
    populateMarketBrowser();
}

void MainWindow::refreshDashboard() {
    populateDashboard();
}

// ===================== DB RESTORE HELPERS =====================

void MainWindow::loadBookingsFromDb() {
    QSqlQuery q(DatabaseManager::instance().db());
    q.exec("SELECT u.username, ms.market_date "
           "FROM stall_bookings sb "
           "JOIN vendors v ON sb.vendor_id = v.vendor_id "
           "JOIN users u ON v.user_id = u.user_id "
           "JOIN market_schedule ms ON sb.market_id = ms.market_id");

    while (q.next()) {
        QString username = q.value("username").toString();
        QString dateStr = q.value("market_date").toString();

        Vendor* vendor = storage.findVendor(username);
        if (!vendor) {
            qWarning() << "loadBookingsFromDb: vendor not found:" << username;
            continue;
        }

        // Find the matching MarketDate
        MarketDate* md = nullptr;
        std::vector<MarketDate>& dates = storage.getMarketDates();
        for (auto& d : dates) {
            if (d.getDate() == dateStr) {
                md = &d;
                break;
            }
        }
        if (!md) {
            qWarning() << "loadBookingsFromDb: market date not found:" << dateStr;
            continue;
        }

        // Restore in-memory state: add vendor to market date slots and booking list
        md->addVendor(vendor);
        Booking* b = new Booking(vendor, md);
        bookingList.addBooking(b);

        qDebug() << "Restored booking:" << username << "on" << dateStr;
    }
}

void MainWindow::loadWaitlistFromDb() {
    QSqlQuery q(DatabaseManager::instance().db());
    q.exec("SELECT u.username, ms.market_date, w.position "
           "FROM waitlist w "
           "JOIN vendors v ON w.vendor_id = v.vendor_id "
           "JOIN users u ON v.user_id = u.user_id "
           "JOIN market_schedule ms ON w.market_id = ms.market_id "
           "WHERE w.status = 'waiting' "
           "ORDER BY ms.market_date, w.position");

    while (q.next()) {
        QString username = q.value("username").toString();
        QString dateStr = q.value("market_date").toString();

        Vendor* vendor = storage.findVendor(username);
        if (!vendor) {
            qWarning() << "loadWaitlistFromDb: vendor not found:" << username;
            continue;
        }

        // Find the matching MarketDate
        MarketDate* md = nullptr;
        std::vector<MarketDate>& dates = storage.getMarketDates();
        for (auto& d : dates) {
            if (d.getDate() == dateStr) {
                md = &d;
                break;
            }
        }
        if (!md) {
            qWarning() << "loadWaitlistFromDb: market date not found:" << dateStr;
            continue;
        }

        // Restore in-memory waitlist (addToWaitlist would re-insert into DB, so use direct access)
        Category cat = vendor->getCategory();
        Waitlist* wl = waitlistManager.getWaitlist(md, cat);
        wl->addVendor(vendor);

        qDebug() << "Restored waitlist:" << username << "on" << dateStr << "pos" << q.value("position").toInt();
    }
}
