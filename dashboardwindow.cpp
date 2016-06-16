#include "dashboardwindow.h"
#include "ui_dashboardwindow.h"

DashboardWindow::DashboardWindow(QWidget *parent, bool isRelative, QString ID) :
    QWidget(parent),
    ui(new Ui::DashboardWindow)
{
    ui->setupUi(this);

    //qDebug() << ID;
    m_RelativeID = ID;
    if (isRelative)
    {
        //qDebug() << "Is relative";
        ui->stackedWidget->setCurrentIndex(1);
        on_pushButton_overview_clicked();
        ui->pushButton_overview->setChecked(1);
    }
    else {
        ui->stackedWidget->setCurrentIndex(0);

        QSqlQueryModel *model = new QSqlQueryModel;

        QString query = "SELECT COUNT(*) FROM INMATE";
        model->setQuery(query);

        ui->txtInmateCount->setText("Number of inmates: " + model->data(model->index(0, 0)).toString());

        query = "SELECT COUNT(*) FROM RE_LATIVE";
        model->setQuery(query);

        ui->txtRelativeCount->setText("Number of relatives: " + model->data(model->index(0, 0)).toString());

        query = "SELECT COUNT(*) FROM OFFICER";
        model->setQuery(query);

        ui->txtOfficerCount->setText("Number of officers: " + model->data(model->index(0, 0)).toString());
    }
}

DashboardWindow::~DashboardWindow()
{
    delete ui;
}

void DashboardWindow::on_pushButton_connect_clicked()   //view detail
{
    InmateInfoWindow * inmateInfo = new InmateInfoWindow(0, m_InmateID, 1);
    inmateInfo->show();
    //emit row_activated(inmateInfo, 0);
}

void DashboardWindow::on_pushButton_connect_2_clicked()
{
    QSqlDatabase db = Database::getDatabase();
    QSqlQueryModel *model = new QSqlQueryModel;
    QString query = "SELECT `mon` AS `Monday`, `tue` AS `Tuesday`, `wed` AS `Wednesday`, `thu` AS `Thursday`, `fri` AS `Friday`, `sat` AS `Saturday`, `sun` AS `Sunday`"
                    "FROM `VISIT_TIMES`";

    model->setQuery(query);
    ui->tblRelatives->setModel(model);
}

void DashboardWindow::on_pushButton_overview_clicked()
{
    QSqlDatabase db = Database::getDatabase();
    QSqlQueryModel *model = new QSqlQueryModel;
    QString query = "SELECT `INMATE`.`ID`, `INMATE`.`Lastname` AS `Last name`, `INMATE`.`Midname` AS `Middle name`, `INMATE`.`Firstname` "
                    "AS `First name`, `INMATE`.`BookIn` AS `Bookin`, "
                    "`INMATE`.`BookOut` AS `Bookout` FROM `INMATE`, `RE_LATIVE` "
                    "WHERE `INMATE`.`ID` = `RE_LATIVE`.`InmateID` AND `RE_LATIVE`.`ID` = N'" + m_RelativeID + "'";

    qDebug() << query;
    model->setQuery(query);
    ui->tblRelatives->setModel(model);
    m_InmateID = model->data(model->index(0, 0)).toString();
}

void DashboardWindow::on_pushButton_connect_3_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString query = "SELECT `MEDCHECKS`.`ID` AS `Record ID`, "
                    "`MEDCHECKS`.`InmateID` AS `Inmate ID`, "
                    "`MEDCHECKS`.`MEDCHECKS_Date` AS `Date`, "
                    "`MEDCHECKS`.`Urgency` AS `Urgency`, "
                    "`MEDCHECKS`.`Condi` AS `Inmate health condition`, "
                    "`MEDCHECKS`.`Remarks` AS `Remarks` FROM `PMS`.`MEDCHECKS`, `PMS`.`RE_LATIVE`, `PMS`.`INMATE` "
                    "WHERE `INMATE`.`ID` = `RE_LATIVE`.`InmateID` AND `MEDCHECKS`.`InmateID` = `INMATE`.`ID` "
                    "AND `RE_LATIVE`.`ID` = N'" + m_RelativeID + "' "
                    "ORDER BY `MEDCHECKS`.`MEDCHECKS_Date`";

    qDebug() << query;
    model->setQuery(query);
    ui->tblRelatives->setModel(model);
}

void DashboardWindow::on_tblRelatives_clicked(const QModelIndex &index)
{
    ui->tblRelatives->selectRow(index.row());
}

void DashboardWindow::on_tblRelatives_pressed(const QModelIndex &index)
{
    ui->tblRelatives->selectRow(index.row());
}
