#include "healthcarewindow.h"
#include "ui_healthcarewindow.h"
#include <QStyleFactory>
#include "database.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <algorithm>
#include <QMessageBox>

HealthcareWindow::HealthcareWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HealthcareWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    QSqlDatabase db = Database::getDatabase();
//    model = new QSqlTableModel(this, db);
//    model->setTable("MEDCHECKS");
//    model->select();

   on_pushButton_HealthRecord_clicked();

    ui->pushSearch->setEnabled(true);
    ui->pushButton_HealthRecord->setChecked(true);

    QSqlQuery qquery(db);
    qquery.exec("SELECT * FROM INMATE");

    while(qquery.next())
    {
        ui->comboBox_inmateID->addItem(qquery.value(0).toString());
    }
}

HealthcareWindow::~HealthcareWindow()
{
    delete ui;
}

void HealthcareWindow::on_pushDelete_clicked()
{
    model->removeRow(ui->tableView->currentIndex().row());
}

void HealthcareWindow::on_pushModify_clicked()
{
    model->select();
}

void HealthcareWindow::on_pushSearch_clicked()
{
    QSqlDatabase db = Database::getDatabase();

    QString name = ui->lineEdit->text();
    QString query;
    query = "SELECT * FROM MEDCHECKS WHERE ID LIKE '%" + name + "%' OR InmateID LIKE '%" + name + "%' OR Condi LIKE '%" + name + "%'";

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query, db);
    ui->tableView->setModel(model);
}

QString getNewMedCheckID(QVector <QString> arrID)
{
    QVector <int> arrNumID(arrID.size());

    for (int i = 0; i < arrID.size(); i++)
    {
        arrNumID[i] = QString(arrID[i].right(3)).toInt();
    }

    qSort(arrNumID.begin(), arrNumID.end());

    int i, numID;
    for (i = 1; i < arrNumID.size(); i++)
    {
        if (arrNumID[i] != arrNumID[i - 1] + 1)
            break;
    }

    if (i == arrNumID.size())
        numID = arrNumID[arrNumID.size() - 1] + 1;
    else
        numID = arrNumID[i] - 1;

    char tmp[4];
    itoa(numID, tmp, 10);
    QString newID(tmp);
    while (newID.length() < 3)
        newID = '0' + newID;
    newID = "MC" + newID;
    return newID;
}

void HealthcareWindow::on_pushAccept_clicked()
{
    if (ui->comboBox_inmateID->currentText() == "")
    {
        QMessageBox::critical(this, "Error", "Invalid ID!");
        return;
    }

    QSqlDatabase db = Database::getDatabase();
    QString QSQuery = "SELECT * FROM INMATE WHERE ID = '" + ui->comboBox_inmateID->currentText() + "'";
    QSqlQuery query(db);
    query.exec(QSQuery);
    if (query.size() < 1)
    {
        QMessageBox::critical(this, "Error", "Invalid inmate ID!");
        return;
    }

    QVector <QString> arrID;
    QSQuery = "SELECT * FROM MEDCHECKS";
    query.exec(QSQuery);

    while(query.next())
    {
        arrID.push_back(query.value(0).toString());
    }

    QString newID = getNewMedCheckID(arrID);
    QSQuery = "INSERT INTO MEDCHECKS VALUES('" + newID + "', '" + ui->comboBox_inmateID->currentText()
            + "', '" + ui->date->text() + " " + ui->time->text().left(ui->time->text().size() - 3)
            + "', NULL, NULL, N'" + ui->remarks->toPlainText() + "')";

    qDebug() << QSQuery;

    query.exec(QSQuery);

    QMessageBox::information(this, "Success", "Complete!");
    ui->comboBox_inmateID->setCurrentText("");
    ui->remarks->setPlainText("");
    ui->date->setDate(QDate(2000,01,01));
    ui->time->setTime(QTime(12, 0, 0));
}

void HealthcareWindow::on_pushButton_HealthRecord_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    QSqlDatabase db = Database::getDatabase();
    QSqlQueryModel * qmodel = new QSqlQueryModel;

    QString query = "SELECT `medchecks`.`ID` AS `Record ID`, "
                    "`medchecks`.`InmateID` AS `Inmate ID`, "
                    "`medchecks`.`MEDCHECKS_Date` AS `Date`, "
                    "`medchecks`.`Urgency` AS `Urgency`, "
                    "`medchecks`.`Condi` AS `Inmate health condition`, "
                    "`medchecks`.`Remarks` AS `Remarks` FROM `pms`.`medchecks`;";
    qDebug() << query;

    qmodel->setQuery(query, db);

    ui->tableView->setModel(qmodel);

    ui->pushSearch->setEnabled(true);
}

void HealthcareWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void HealthcareWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void HealthcareWindow::on_tableView_pressed(const QModelIndex &index)
{
    ui->tableView->selectRow(index.row());
}

void HealthcareWindow::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    QSqlDatabase db = Database::getDatabase();

    QSqlQueryModel * qmodel = new QSqlQueryModel;

    QString query = "SELECT `medchecks`.`ID` AS `Record ID`, "
                    "`medchecks`.`InmateID` AS `Inmate ID`, "
                    "`medchecks`.`MEDCHECKS_Date` AS `Date`, "
                    "`medchecks`.`Urgency` AS `Urgency`, "
                    "`medchecks`.`Condi` AS `Inmate health condition`, "
                    "`medchecks`.`Remarks` AS `Remarks FROM `pms`.`medchecks` "
                    "WHERE `medchecks`.`Urgency` = 'High';";

    qmodel->setQuery(query, db);

    ui->tableView->setModel(qmodel);

    ui->pushSearch->setEnabled(true);
}

void HealthcareWindow::on_pushButton_17_clicked(bool checked)
{

}
