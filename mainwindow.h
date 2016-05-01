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
    void on_toolButton_Dashboard_clicked();

    void on_toolButton_Dining_clicked();

    void on_toolButton_Healthcare_clicked();

    void on_toolButton_etrr_clicked();

    void on_toolButton_rehab_clicked();

    void on_toolButton_mng_clicked();

private:
    Ui::MainWindow *ui;

    // Pointers to regulate instancing of subwindow classes
    // These pointers mainly serve to help avoid spawning multiple instances
    // of the same subwindow class.

    DashboardWindow *dashboard;
    HealthcareWindow *healthcare;
    DiningWindow *dining;
    EntryReleaseForm *etrr;
    RehabForm *rehab;
    ManagementWindow *mng;

    // Pointers to manage the subwindow themselves
    // These pointers are required for switching between multiple subwindows
    // as "tabs" on the main window.

    QMdiSubWindow *sub_dashboard;
    QMdiSubWindow *sub_healthcare;
    QMdiSubWindow *sub_dining;
    QMdiSubWindow *sub_etrr;
    QMdiSubWindow *sub_rehab;
    QMdiSubWindow *sub_mng;
};

#endif // MAINWINDOW_H
