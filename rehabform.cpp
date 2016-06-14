#include "rehabform.h"
#include "ui_rehabform.h"

RehabForm::RehabForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RehabForm)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    model = new QSqlQueryModel;

    on_pushButton_16_clicked();

    ui->pushButton_16->setChecked(true);

}

RehabForm::~RehabForm()
{
    delete ui;
}

void RehabForm::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    QSqlDatabase db = Database::getDatabase();

    QString query = "SELECT `rehabilitation`.`OfficerID` AS `Officer in charge`, `rehabilitation`.`InmateID` AS `Inmate ID`, "
                    "`rehabilitation`.`R_level` AS `Progress`, `rehabilitation`.`Ludate` AS `Last updated`, `rehabilitation`.`Talents` AS `Talents`, "
                    "`rehabilitation`.`Recommendation` AS `Recommendations`, `rehabilitation`.`Reward` AS `Rewards`, `rehabilitation`.`Remarks` AS `Remarks`"
                    "FROM `pms`.`rehabilitation`;";
    model->setQuery(query, db);
    ui->tableView->setModel(model);

    ui->pushSearch->setEnabled(true);
}

void RehabForm::on_pushAdd_clicked()
{
    model->insertRow(model->rowCount());
    QSqlQuery satan_approves;
    QString log = "INSERT INTO LOG (department, logtime, content) VALUES ('Rehabilitation', "
            "CAST(N'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm") + "' AS Datetime), "
            "N'Record added.')";
    satan_approves.prepare(log);
    satan_approves.exec();
}

void RehabForm::on_pushDelete_clicked()
{
    model->removeRow(ui->tableView->currentIndex().row());
    QSqlQuery satan_approves;
    QString log = "INSERT INTO LOG (department, logtime, content) VALUES ('Rehabilitation', "
            "CAST(N'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm") + "' AS Datetime), "
            "N'Record deleted.')";
    satan_approves.prepare(log);
    satan_approves.exec();
}

void RehabForm::on_pushModify_clicked()
{
    //model->select();
}


void RehabForm::on_pushSearch_clicked()
{
    QSqlDatabase db = Database::getDatabase();

    QString name = ui->lineEdit->text();
    QString query;
    query = "SELECT * FROM REHABILITATION WHERE OfficerID LIKE '%" + name + "%' OR InmateID LIKE '%" + name + "%' OR R_level LIKE '%" + name + "%'";

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query, db);
    ui->tableView->setModel(model);
}

void RehabForm::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void RehabForm::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void RehabForm::on_pushButton_4_clicked()
{
    QSqlDatabase db = Database::getDatabase();
    QString query;
    query = ui->txtQuery->toPlainText();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query, db);
    ui->tableView->setModel(model);
    ui->stackedWidget->setCurrentIndex(0);
}

void RehabForm::on_pushButton_5_clicked()
{
    ui->txtQuery->clear();
}

void RehabForm::on_tableView_pressed(const QModelIndex &index)
{
    ui->tableView->selectRow(index.row());
}
