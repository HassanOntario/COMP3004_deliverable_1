#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "vendor.h"
#include "storage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    const Vendor* itemIn(const std::vector<Vendor>& list, const QString& element) const;

private slots:
    void on_p1Button_clicked();
    void on_returnLogin_clicked();
    void on_vDash_clicked();
    void on_vBrowse_clicked();
    void on_vHome_clicked();

private:
    Ui::MainWindow *ui;
    Storage storage;
    const Vendor* vendorUser;


};





#endif // MAINWINDOW_H
