#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "storage.h"
#include "vendor.h"

#include <QString>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->returnLogin->hide();
    ui->vBrowse->hide();
    ui->vDash->hide();
    ui->vHome->hide();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_p1Button_clicked() {

    storage.loadData();

    const auto& vendors = storage.getVendors();


    QString username = ui->userInput->text();

    // here we can put the code for checking against our in memory database to see if the user is within the system


    const Vendor* user = itemIn(vendors, username);

    qDebug() << (user == nullptr);
    qDebug() << user;

    if (user != nullptr) {
        ui->loginScreen->setCurrentWidget(ui->vendorPage);
        ui->vendorLabel->setText("welcome vendor, " + username);

        // show all the buttons in  the toolbar when the user is logged in as a vendor (like dashboard, home, browse)
        ui->vBrowse->show();
        ui->vDash->show();
        ui->vHome->show();

        // we are on the home page so we disable that button
        ui->vDash->setEnabled(true);
        ui->vBrowse->setEnabled(true);
        ui->vHome->setEnabled(false);

        DashboardControl vendorUser(user);
        dControl = vendorUser;


    } else if (username == storage.getAdmin().getUsername()) {
        ui->loginScreen->setCurrentWidget(ui->adminPage);
        ui->adminLabel->setText("welcome administrator, " + username);

    } else if (username == storage.getOrganizer().getUsername()) {
        ui->loginScreen->setCurrentWidget(ui->orgPage);
        ui->orgLabel->setText("welcome organizer, " + username);

    } else {
        ui->errorLabel->setText("please enter a valid username");
        return;
    }

    ui->returnLogin->show();


}

void MainWindow::on_returnLogin_clicked() {
    ui->loginScreen->setCurrentWidget(ui->page);

    // hide all buttons in the 'toolbar' / header
    ui->returnLogin->hide();
    ui->vBrowse->hide();
    ui->vDash->hide();
    ui->vHome->hide();

    // reset the text inside the input bar for the username
    ui->userInput->setText("");



}

void MainWindow::on_vDash_clicked() {
    const Vendor* vendorUser = dControl.getVendor();

    ui->loginScreen->setCurrentWidget(ui->vendorDashboard);

    // set the current button of the page we are on to be disabled so there is no redundancy in clicking it over and also for the user to be able to tell what page they are on
    ui->vDash->setEnabled(false);
    ui->vBrowse->setEnabled(true);
    ui->vHome->setEnabled(true);

    // BUSINESS INFORMATION
    ui->dashBusiness->setText(vendorUser->getBusinessInfo().name);

    ui->dashOwner->setText(vendorUser->getBusinessInfo().ownerName);

    ui->dashEmail->setText(vendorUser->getBusinessInfo().emailAddress);
    ui->dashAddress->setText(vendorUser->getBusinessInfo().mailingAddress);
    ui->dashAddress->setWordWrap(true);
    ui->dashPhone->setText(QString::number(vendorUser->getBusinessInfo().phoneNumber));

    if (vendorUser->getCategory() == 0) {
        ui->dashCategory->setText("Food");

        ui->dashFood->show();

        ui->dashCert->setText(QString::number(vendorUser->getFoodHandlerCert().certNum));
        ui->dashCertExp->setText(vendorUser->getFoodHandlerCert().expirationDate);

    } else if (vendorUser->getCategory() == 1) {
        ui->dashCategory->setText("Artisan");

        // artisans only have the 2 compliance documents so we can hide the Food Cert details to display their documents
        ui->dashFood->hide();
        ui->dashCert->setText("");
        ui->dashCertExp->setText("");
    }

    // COMPLIANCE DOCUMENTATION STATUS

    ui->dashBus->setText(QString::number(vendorUser->getBusinessLicence().licenceNum));
    ui->dashBusExp->setText(vendorUser->getBusinessLicence().expirationDate);

    ui->dashIns->setText(QString::number(vendorUser->getLiabilityInsurance().policyNum));
    ui->dashInsExp->setText(vendorUser->getLiabilityInsurance().expirationDate);
    ui->dashInsProv->setText("provided by: " + vendorUser->getLiabilityInsurance().insuranceProvider);



}


void MainWindow::on_vBrowse_clicked() {
    // ui->loginScreen->setCurrentWidget(ui->);
}

void MainWindow::on_vHome_clicked() {
    ui->loginScreen->setCurrentWidget(ui->vendorPage);

    ui->vDash->setEnabled(true);
    ui->vBrowse->setEnabled(true);
    ui->vHome->setEnabled(false);

}

const Vendor* MainWindow::itemIn(const std::vector<Vendor>& list, const QString& element) const {
    for (auto& item : list) {
        if (element == item.getUsername()) {
            return &item;
        }
    }
    return nullptr;
}
