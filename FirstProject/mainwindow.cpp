#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->returnLogin->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_p1Button_clicked() {


    QString username = ui->userInput->text();

    // here we can put the code for checking against our in memory database to see if the user is within the system

    // simple as of now but when we have the storage set up we can check against the database to know where to send the user
    if (username == "vendor"){
        ui->loginScreen->setCurrentWidget(ui->vendorPage);
        ui->vendorLabel->setText("welcome vendor, " + username);

    } else if (username == "organizer") {
        ui->loginScreen->setCurrentWidget(ui->orgPage);
        ui->orgLabel->setText("welcome organizer, " + username);

    } else if (username == "admin") {
        ui->loginScreen->setCurrentWidget(ui->adminPage);
        ui->adminLabel->setText("welcome administrator, " + username);

    } else {
        ui->errorLabel->setText("please enter a valid username");
        return;
    }

    ui->returnLogin->show();

}

void MainWindow::on_returnLogin_clicked() {
    ui->loginScreen->setCurrentWidget(ui->page);
    ui->returnLogin->hide();
}
