#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dashboard = new DashboardWindow;
    sub_dashboard = ui->mdiArea->addSubWindow(dashboard, Qt::FramelessWindowHint);
    dashboard->showMaximized();
    dashboard->activateWindow();
    ui->toolButton_Dashboard->setChecked(true);

    healthcare = NULL;
    dining = NULL;
    etrr = NULL;
    rehab = NULL;
    mng = NULL;

    sub_healthcare = NULL;
    sub_dining = NULL;
    sub_etrr = NULL;
    sub_rehab = NULL;
    sub_mng = NULL;
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
    delete ui;
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
    ui->toolButton_Dashboard->setChecked(true);
    ui->toolButton_Dining->setChecked(false);
    ui->toolButton_Healthcare->setChecked(false);
    ui->toolButton_etrr->setChecked(false);
    ui->toolButton_rehab->setChecked(false);
    ui->toolButton_mng->setChecked(false);
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
    ui->toolButton_Dining->setChecked(true);
    ui->toolButton_Healthcare->setChecked(false);
    ui->toolButton_Dashboard->setChecked(false);
    ui->toolButton_etrr->setChecked(false);
    ui->toolButton_rehab->setChecked(false);
    ui->toolButton_mng->setChecked(false);
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
    ui->toolButton_Healthcare->setChecked(true);
    ui->toolButton_Dining->setChecked(false);
    ui->toolButton_Dashboard->setChecked(false);
    ui->toolButton_etrr->setChecked(false);
    ui->toolButton_rehab->setChecked(false);
    ui->toolButton_mng->setChecked(false);
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
    ui->toolButton_etrr->setChecked(true);
    ui->toolButton_Dining->setChecked(false);
    ui->toolButton_Dashboard->setChecked(false);
    ui->toolButton_Healthcare->setChecked(false);
    ui->toolButton_rehab->setChecked(false);
    ui->toolButton_mng->setChecked(false);
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
    ui->toolButton_rehab->setChecked(true);
    ui->toolButton_Dining->setChecked(false);
    ui->toolButton_Dashboard->setChecked(false);
    ui->toolButton_etrr->setChecked(false);
    ui->toolButton_Healthcare->setChecked(false);
    ui->toolButton_mng->setChecked(false);
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
    ui->toolButton_mng->setChecked(true);
    ui->toolButton_Dining->setChecked(false);
    ui->toolButton_Dashboard->setChecked(false);
    ui->toolButton_etrr->setChecked(false);
    ui->toolButton_rehab->setChecked(false);
    ui->toolButton_Healthcare->setChecked(false);
}
