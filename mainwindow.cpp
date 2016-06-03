#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow(int OfficerType, QString ID, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dashboard = new DashboardWindow;
    sub_dashboard = ui->mdiArea->addSubWindow(dashboard, Qt::FramelessWindowHint);
    dashboard->showMaximized();
    dashboard->activateWindow();
    ui->toolButton_Dashboard->setChecked(true);

    ui->nameID->setText(ID);

    SetPermission(OfficerType);

    healthcare = NULL;
    dining = NULL;
    etrr = NULL;
    rehab = NULL;
    mng = NULL;
    system = NULL;

    sub_healthcare = NULL;
    sub_dining = NULL;
    sub_etrr = NULL;
    sub_rehab = NULL;
    sub_mng = NULL;
    sub_system = NULL;
}

MainWindow::~MainWindow()
{
    if (Database::isConnected())
    {
        Database::Release();
    }

    if (dashboard)
    {
        delete dashboard;
        dashboard = NULL;
    }

    if (healthcare)
    {
        delete healthcare;
        healthcare = NULL;
    }

    if (dining)
    {
        delete dining;
        dining = NULL;
    }

    if (etrr)
    {
        delete etrr;
        etrr = NULL;
    }

    if (rehab)
    {
        delete rehab;
        rehab = NULL;
    }

    if (mng)
    {
        delete mng;
        mng = NULL;
    }

    if (system)
    {
        delete system;
        system = NULL;
    }
    delete ui;
}

void MainWindow::SetPermission(int OfficerType)
{
    if (OfficerType == RELATIVETYPE)
    {
        ui->toolButton_Dining->setEnabled(false);
        ui->toolButton_etrr->setEnabled(false);
        ui->toolButton_Healthcare->setEnabled(false);
        ui->toolButton_mng->setEnabled(false);
        ui->toolButton_rehab->setEnabled(false);
        ui->permision->setText("Relative");
    }
    else if (OfficerType == DININGTYPE)
    {
        ui->toolButton_etrr->setEnabled(false);
        ui->toolButton_Healthcare->setEnabled(false);
        ui->toolButton_mng->setEnabled(false);
        ui->toolButton_rehab->setEnabled(false);
        ui->permision->setText("Dining");
    }
    else if (OfficerType == HEALTHCARETYPE)
    {
        ui->toolButton_Dining->setEnabled(false);
        ui->toolButton_etrr->setEnabled(false);
        ui->toolButton_mng->setEnabled(false);
        ui->toolButton_rehab->setEnabled(false);
        ui->permision->setText("Health care");
    }
    else if (OfficerType == ENTRY_RELEASETYPE)
    {
        ui->toolButton_Dining->setEnabled(false);
        ui->toolButton_Healthcare->setEnabled(false);
        ui->toolButton_mng->setEnabled(false);
        ui->toolButton_rehab->setEnabled(false);
        ui->permision->setText("Entry & Release");
    }
    else if (OfficerType == REHABILITATIONTYPE)
    {
        ui->toolButton_Dining->setEnabled(false);
        ui->toolButton_etrr->setEnabled(false);
        ui->toolButton_Healthcare->setEnabled(false);
        ui->toolButton_mng->setEnabled(false);
        ui->permision->setText("Rehabilitation");
    }
    else if (OfficerType == MANAGETYPE)
    {
        ui->toolButton_Dining->setEnabled(false);
        ui->toolButton_etrr->setEnabled(false);
        ui->toolButton_Healthcare->setEnabled(false);
        ui->toolButton_rehab->setEnabled(false);
        ui->permision->setText("Management");
    }
}

void MainWindow::on_toolButton_Dashboard_clicked()
{
    if (sub_dashboard == NULL) {
        dashboard = new DashboardWindow;
        sub_dashboard = ui->mdiArea->addSubWindow(dashboard, Qt::FramelessWindowHint);
        dashboard->showMaximized();
        dashboard->activateWindow();
    }
    else ui->mdiArea->setActiveSubWindow(sub_dashboard);
}

void MainWindow::on_toolButton_Dining_clicked()
{
    if (sub_dining == NULL) {
       dining = new DiningWindow;
       sub_dining = ui->mdiArea->addSubWindow(dining, Qt::FramelessWindowHint);
       dining->showMaximized();
       dining->activateWindow();
    }
    else ui->mdiArea->setActiveSubWindow(sub_dining);
}

void MainWindow::on_toolButton_Healthcare_clicked()
{
    if (sub_healthcare == NULL) {
      healthcare = new HealthcareWindow;
      sub_healthcare = ui->mdiArea->addSubWindow(healthcare, Qt::FramelessWindowHint);
      healthcare->showMaximized();
      healthcare->activateWindow();
    }
    else ui->mdiArea->setActiveSubWindow(sub_healthcare);
}

void MainWindow::on_toolButton_etrr_clicked()
{
    if (sub_etrr == NULL) {
       etrr = new EntryReleaseForm;
       sub_etrr = ui->mdiArea->addSubWindow(etrr, Qt::FramelessWindowHint);
       etrr->showMaximized();
       etrr->activateWindow();
    }
    else ui->mdiArea->setActiveSubWindow(sub_etrr);
}

void MainWindow::on_toolButton_rehab_clicked()
{
    if (sub_rehab == NULL) {
       rehab = new RehabForm;
       sub_rehab = ui->mdiArea->addSubWindow(rehab, Qt::FramelessWindowHint);
       rehab->showMaximized();
       rehab->activateWindow();
    }
    else ui->mdiArea->setActiveSubWindow(sub_rehab);
}

void MainWindow::on_toolButton_mng_clicked()
{
    if (sub_mng == NULL) {
       mng = new ManagementWindow;
       sub_mng = ui->mdiArea->addSubWindow(mng, Qt::FramelessWindowHint);
       mng->showMaximized();
       mng->activateWindow();
    }
    else ui->mdiArea->setActiveSubWindow(sub_mng);
}


void MainWindow::on_system_clicked()
{
    if (sub_system == NULL) {
       system = new systemwindow;
       sub_system = ui->mdiArea->addSubWindow(system, Qt::FramelessWindowHint);
       system->showMaximized();
       system->activateWindow();
    }
    else ui->mdiArea->setActiveSubWindow(sub_system);
}
