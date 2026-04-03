#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QMessageBox>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <vector>

#include "vendor.h"
#include "storage.h"
#include "bookinglist.h"
#include "waitlistmanager.h"
#include "stallbookingcontrol.h"
#include "dashboardcontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_p1Button_clicked();
    void on_returnLogin_clicked();
    void on_vDash_clicked();
    void on_vBrowse_clicked();
    void on_vHome_clicked();

private:
    Ui::MainWindow *ui;

    // Data layer
    Storage storage;
    BookingList bookingList;
    WaitlistManager waitlistManager;
    StallBookingControl* stallBookingControl;

    // Current session
    Vendor* currentVendor;

    // Helper methods
    void populateDashboard();
    void populateMarketBrowser();
    void setupMarketBrowserPage();
    void handleBookStall(int marketIndex);
    void handleCancelBooking(int marketIndex);
    void handleJoinWaitlist(int marketIndex);
    void handleLeaveWaitlist(int marketIndex);
    void refreshMarketBrowser();
    void refreshDashboard();
    void loadBookingsFromDb();
    void loadWaitlistFromDb();

    // Operator page methods
    void setupOperatorPage();
    void refreshOperatorStatus();
    void handleOperatorBook();
    void handleOperatorCancel();
    void handleOperatorRemoveWaitlist();

    // Market browser UI elements (built programmatically)
    QWidget* marketBrowserPage;
    QTableWidget* marketTable;

    // Operator page UI elements (built programmatically)
    QWidget* operatorPage;
    QComboBox* opVendorCombo;
    QComboBox* opDateCombo;
    QLabel* opStatusLabel;
    QTableWidget* opInfoTable;
};

#endif // MAINWINDOW_H
