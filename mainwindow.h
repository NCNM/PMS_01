#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QDebug>
#include "database.h"
#include "ui_mainwindow.h"
#include "dashboardwindow.h"
#include "healthcarewindow.h"
#include "diningwindow.h"
#include "rehabform.h"
#include "entryreleaseform.h"
#include "managementwindow.h"
#include "database.h"
#include "idofficertype.h"
#include "systemwindow.h"
#include "inmateinfowindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int OfficerType = -1, QString ID = "unknown ID", QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_toolButton_Dashboard_clicked();

    void on_toolButton_Dining_clicked();

    void on_toolButton_Healthcare_clicked();

    void on_toolButton_etrr_clicked();

    void on_toolButton_rehab_clicked();

    void on_toolButton_mng_clicked();

    void on_system_clicked();

    void view_inmate_details(InmateInfoWindow* child, int parent);

    void details_closed();

    void echo_status(QString content);

private:
    Ui::MainWindow *ui;

    void SetPermission(int OfficerType);
    // Pointers to regulate instancing of subwindow classes
    // These pointers mainly serve to help avoid spawning multiple instances
    // of the same subwindow class.

    DashboardWindow *dashboard;
    HealthcareWindow *healthcare;
    DiningWindow *dining;
    EntryReleaseForm *etrr;
    RehabForm *rehab;
    ManagementWindow *mng;
    systemwindow *system;

    // Pointers to manage the subwindow themselves
    // These pointers are required for switching between multiple subwindows
    // as "tabs" on the main window.

    QMdiSubWindow *sub_dashboard;
    QMdiSubWindow *sub_healthcare;
    QMdiSubWindow *sub_dining;
    QMdiSubWindow *sub_etrr;
    QMdiSubWindow *sub_rehab;
    QMdiSubWindow *sub_mng;
    QMdiSubWindow *sub_system;
    QMdiSubWindow *current_sub;

    int m_OfficerType;
    QString m_ID;
};

#endif // MAINWINDOW_H
