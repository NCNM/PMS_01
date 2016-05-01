#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget()->layout()->setSpacing(0);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
    centralWidget()->layout()->setSizeConstraint(QLayout::SetMaximumSize);

    dashboard = new DashboardWindow;
    ui->mdiArea->addSubWindow(dashboard, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
    dashboard->showMaximized();
    dashboard->activateWindow();
    ui->toolButton_Dashboard->setChecked(true);


    healthcare = NULL;
    dining = NULL;
    etrr = NULL;
    rehab = NULL;
    mng = NULL;
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

void MainWindow::on_toolButton_Dashboard_clicked(bool checked)
{
    if (checked == true) {
       if(dashboard == NULL){
       dashboard = new DashboardWindow;
       }

       dashboard->showMaximized();
       dashboard->activateWindow();
    }
}

void MainWindow::on_actionTest_login_triggered()
{
    //LoginWindow *lgn = new LoginWindow;
    //lgn->show();
}

void MainWindow::on_toolButton_clicked(bool checked)
{

}

void MainWindow::on_toolButton_Healthcare_clicked(bool checked)
{
    if(checked == true){
        if(healthcare == NULL){
        healthcare = new HealthcareWindow;
        ui->mdiArea->addSubWindow(healthcare, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
        }
        healthcare->showMaximized();
        healthcare->activateWindow();
    }

}

void MainWindow::on_toolButton_Dining_clicked(bool checked)
{
    if (checked == true) {
       if(dining==NULL){
       dining = new DiningWindow;
       ui->mdiArea->addSubWindow(dining, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
       }
       dining->showMaximized();
       dining->activateWindow();
    }

}

void MainWindow::on_toolButton_etrr_clicked(bool checked)
{
    if (checked == true) {
       if(etrr==NULL){
       etrr = new EntryReleaseForm;
       ui->mdiArea->addSubWindow(etrr, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
       }
       etrr->showMaximized();
       etrr->activateWindow();
    }

}

void MainWindow::on_toolButton_rehab_clicked(bool checked)
{
    if (checked == true) {
       if(rehab==NULL){
       rehab = new RehabForm;
       ui->mdiArea->addSubWindow(rehab, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
       }
       rehab->showMaximized();
       rehab->activateWindow();
    }

}

void MainWindow::on_toolButton_mng_clicked(bool checked)
{
    if (checked == true) {
       if(mng == NULL){
       mng = new ManagementWindow;
       ui->mdiArea->addSubWindow(mng, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
       }
       mng->showMaximized();
       mng->activateWindow();
    }
}

void MainWindow::closeEvent (QCloseEvent *event){
    return; // To avoid "Stopped working" nags from Windows, which should be investigated soon
}

