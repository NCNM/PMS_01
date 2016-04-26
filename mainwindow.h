#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"
#include "ui_mainwindow.h"
#include "dashboardwindow.h"
#include "healthcarewindow.h"
#include "diningwindow.h"
#include "rehabform.h"
#include "entryreleaseform.h"
#include "managementwindow.h"
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionTest_login_triggered();

    void on_toolButton_Dashboard_clicked(bool checked);

    void on_toolButton_clicked(bool checked);

    void on_toolButton_Healthcare_clicked(bool checked);

    void on_toolButton_Dining_clicked(bool checked);

    void on_toolButton_etrr_clicked(bool checked);

    void on_toolButton_rehab_clicked(bool checked);

    void on_toolButton_mng_clicked(bool checked);

private:
    Ui::MainWindow *ui;

    void closeEvent(QCloseEvent *event);

    DashboardWindow *dashboard;
    HealthcareWindow *healthcare;
    DiningWindow *dining;
    EntryReleaseForm *etrr;
    RehabForm *rehab;
    ManagementWindow *mng;
};

#endif // MAINWINDOW_H
