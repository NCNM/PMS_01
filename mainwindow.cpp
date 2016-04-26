#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dashboardwindow.h"
#include "healthcarewindow.h"
#include "diningwindow.h"
#include "rehabform.h"
#include "entryreleaseform.h"
#include "managementwindow.h"
#include "loginwindow.h"
#include "database.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget()->layout()->setSpacing(0);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
    centralWidget()->layout()->setSizeConstraint(QLayout::SetMaximumSize);

    LoginWindow *lgn = new LoginWindow;
    lgn->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_Dashboard_clicked(bool checked)
{
    if (checked == true) {
       DashboardWindow *dashboard = new DashboardWindow;
       ui->mdiArea->addSubWindow(dashboard, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
       dashboard->showMaximized();
       dashboard->activateWindow();
    }
}

void MainWindow::on_actionTest_login_triggered()
{
    LoginWindow *lgn = new LoginWindow;
    lgn->show();
}

void MainWindow::on_toolButton_clicked(bool checked)
{

}

void MainWindow::on_toolButton_Healthcare_clicked(bool checked)
{
    if (checked == true) {
       HealthcareWindow *healthcare = new HealthcareWindow;
       ui->mdiArea->addSubWindow(healthcare, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
       healthcare->showMaximized();
       healthcare->activateWindow();
    }
}

void MainWindow::on_toolButton_Dining_clicked(bool checked)
{
    if (checked == true) {
       DiningWindow *dining = new DiningWindow;
       ui->mdiArea->addSubWindow(dining, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
       dining->showMaximized();
       dining->activateWindow();
    }
}

void MainWindow::on_toolButton_etrr_clicked(bool checked)
{
    if (checked == true) {
       EntryReleaseForm *etrr = new EntryReleaseForm;
       ui->mdiArea->addSubWindow(etrr, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
       etrr->showMaximized();
       etrr->activateWindow();
    }
}

void MainWindow::on_toolButton_rehab_clicked(bool checked)
{
    if (checked == true) {
       RehabForm *rehab = new RehabForm;
       ui->mdiArea->addSubWindow(rehab, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
       rehab->showMaximized();
       rehab->activateWindow();
    }
}

void MainWindow::on_toolButton_mng_clicked(bool checked)
{
    if (checked == true) {
       ManagementWindow *mng = new ManagementWindow;
       ui->mdiArea->addSubWindow(mng, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
       mng->showMaximized();
       mng->activateWindow();
    }
}
