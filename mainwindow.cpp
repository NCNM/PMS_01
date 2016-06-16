#include "mainwindow.h"

MainWindow::MainWindow(int OfficerType, QString ID, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_ID = ID;
    ui->nameID->setText(m_ID);

    m_OfficerType = OfficerType;
    //qDebug() << m_OfficerType;

    SetPermission(m_OfficerType);

    dashboard = NULL;
    healthcare = NULL;
    dining = NULL;
    etrr = NULL;
    rehab = NULL;
    mng = NULL;
    system = NULL;

    sub_dashboard = NULL;
    sub_healthcare = NULL;
    sub_dining = NULL;
    sub_etrr = NULL;
    sub_rehab = NULL;
    sub_mng = NULL;
    sub_system = NULL;

    QString query = "INSERT INTO LOG (department, logtime, content) VALUES ('Maintenance', "
            "CAST(N'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "' AS Datetime), "
            "N'User " + ui->nameID->text() + " logged in.')";

    QSqlQuery satan_approves;
    satan_approves.prepare(query);
    satan_approves.exec();

    ui->statusBar->showMessage("Finished loading.", 5000);

    on_toolButton_Dashboard_clicked();
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
        ui->permision->setText("Healthcare");
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
    else if (OfficerType == ADMINTYPE)
    {
        ui->nameID->setText("admin");
        ui->permision->setText("Administrator");
    }
}

void MainWindow::on_toolButton_Dashboard_clicked()
{
    //qDebug() << "Dashboard";
    if (sub_dashboard == NULL) {
        if (m_OfficerType == RELATIVETYPE)
        {
            dashboard = new DashboardWindow(0, true, m_ID);
            //qDebug() << "Is releative " + m_ID;
        }
        else
        {
            dashboard = new DashboardWindow(0, false);
            //qDebug() << "Is not relative";
        }
        sub_dashboard = ui->mdiArea->addSubWindow(dashboard, Qt::FramelessWindowHint);
        dashboard->showMaximized();
        dashboard->activateWindow();
    }
    else
        ui->mdiArea->setActiveSubWindow(sub_dashboard);
    ui->toolButton_Dashboard->setChecked(true);
}

void MainWindow::on_toolButton_Dining_clicked()
{
    if (sub_dining == NULL) {
       dining = new DiningWindow;
       connect(dining, &DiningWindow::row_activated, this, &MainWindow::view_inmate_details);
       connect(dining, &DiningWindow::send_status, this, &MainWindow::echo_status);
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
      connect(healthcare, &HealthcareWindow::send_status, this, &MainWindow::echo_status);
      healthcare->showMaximized();
      healthcare->activateWindow();
    }
    else ui->mdiArea->setActiveSubWindow(sub_healthcare);
}

void MainWindow::on_toolButton_etrr_clicked()
{
    if (sub_etrr == NULL) {
       etrr = new EntryReleaseForm;
       connect(etrr, &EntryReleaseForm::row_activated, this, &MainWindow::view_inmate_details);
       connect(etrr, &EntryReleaseForm::send_status, this, &MainWindow::echo_status);
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
       connect(mng, &ManagementWindow::row_activated, this, &MainWindow::view_inmate_details);
       connect(mng, &ManagementWindow::send_status, this, &MainWindow::echo_status);
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

void MainWindow::view_inmate_details(InmateInfoWindow* child, int parent)
{
        current_sub = ui->mdiArea->currentSubWindow();
        connect(child, &InmateInfoWindow::go_back, this, &MainWindow::details_closed);
        ui->mdiArea->addSubWindow(child, Qt::FramelessWindowHint);
        child->showMaximized();
        child->activateWindow();
}

void MainWindow::details_closed()
{
    ui->mdiArea->setActiveSubWindow(current_sub);
}

void MainWindow::echo_status(QString content) {
    ui->statusBar->showMessage(content, 5000);
}
