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
    else
        ui->stackedWidget->setCurrentIndex(0);
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

    //qDebug() << query;RE001
    model->setQuery(query);
    ui->tblRelatives->setModel(model);
}

void DashboardWindow::on_pushButton_overview_clicked()
{
    QSqlDatabase db = Database::getDatabase();
    QSqlQueryModel *model = new QSqlQueryModel;
    QString query = "SELECT `INMATE`.`ID`, `INMATE`.`Lastname` AS `Last name`, `INMATE`.`Midname` AS `Mid name`, `INMATE`.`Firstname` AS `First name`, `INMATE`.`BookIn` AS `Bookin`, `INMATE`.`BookOut` AS `Bookout`, `MED`.`MEDCHECKS_Date` AS `Medcheck date`, `MED`.`Urgency`, `MED`.`Condi` AS `Condition`, `MED`.`Remarks`"
                    "FROM `INMATE`, "
                    "   (	SELECT `MEDCHECKS`.`InmateID`, `MEDCHECKS`.`MEDCHECKS_Date`, `MEDCHECKS`.`Urgency`, `MEDCHECKS`.`Condi`, `MEDCHECKS`.`Remarks`"
                    "       FROM `MEDCHECKS`"
                    "       ORDER BY `MEDCHECKS`.`MEDCHECKS_Date` DESC"
                    "       LIMIT 1"
                    "   ) AS `MED`,"
                    "`RE_LATIVE`"
                    "WHERE `INMATE`.`ID` = `RE_LATIVE`.`InmateID` AND `MED`.`InmateID` = `INMATE`.`ID` AND `RE_LATIVE`.`ID` = '" + m_RelativeID + "'";

    qDebug() << query;
    model->setQuery(query);
    ui->tblRelatives->setModel(model);
    m_InmateID = model->data(model->index(0, 0)).toString();
}
