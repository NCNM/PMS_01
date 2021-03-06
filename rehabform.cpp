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
    ui->tableView->resizeColumnsToContents();

    ui->pushSearch->setEnabled(true);
}

void RehabForm::on_pushAdd_clicked()
{
    newrehabform * reha = new newrehabform(0, 0);
    connect(reha, &newrehabform::exec_query, this, &RehabForm::execQuery);
    reha->show();
}

void RehabForm::on_pushDelete_clicked()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this entry?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes)
      {
          QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
          if (indexes.isEmpty())
              return;
          QModelIndex index = indexes.at(0);
          QString IDInm = index.sibling(index.row(), 1).data().toString();

          QSqlDatabase db = Database::getDatabase();

          QSqlQuery query(db);
          query.exec("DELETE FROM REHABILITATION WHERE InmateID = '" + IDInm + "'");
          QString log = "INSERT INTO LOG (department, logtime, content) VALUES ('Rehabilitation', "
                  "CAST(N'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm") + "' AS Datetime), "
                  "N'Record deleted.')";
          query.exec(log);
          on_pushButton_16_clicked();
      }
}

void RehabForm::on_pushModify_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    if (indexes.isEmpty())
        return;
    QModelIndex index = indexes.at(0);
    QString IDInm = index.sibling(index.row(), 1).data().toString();

    newrehabform * reha = new newrehabform(0, 1, IDInm);
    connect(reha, &newrehabform::exec_query, this, &RehabForm::execQuery);
    reha->show();
}


void RehabForm::on_pushSearch_clicked()
{
    QSqlDatabase db = Database::getDatabase();

    QString name = ui->lineEdit->text();
    QString query;
    query = "SELECT `rehabilitation`.`OfficerID` AS `Officer in charge`, `rehabilitation`.`InmateID` AS `Inmate ID`, "
            "`rehabilitation`.`R_level` AS `Progress`, `rehabilitation`.`Ludate` AS `Last updated`, `rehabilitation`.`Talents` AS `Talents`, "
            "`rehabilitation`.`Recommendation` AS `Recommendations`, `rehabilitation`.`Reward` AS `Rewards`, `rehabilitation`.`Remarks` AS `Remarks` "
            "FROM REHABILITATION WHERE OfficerID LIKE '%" + name + "%' OR InmateID LIKE '%" + name + "%' OR R_level LIKE '%" + name + "%'";

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query, db);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
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
    ui->tableView->resizeColumnsToContents();
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

void RehabForm::execQuery(QString Squery)
{
    QSqlDatabase db = Database::getDatabase();
    QSqlQuery query(db);
    query.exec(Squery);

    on_pushButton_16_clicked();

    QString log = "INSERT INTO LOG (department, logtime, content) VALUES ('Rehabilitation', "
            "CAST(N'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm") + "' AS Datetime), "
            "N'Record changed.')";
    query.exec(log);
}

void RehabForm::on_tableView_clicked(const QModelIndex &index)
{
    ui->tableView->selectRow(index.row());
}

void RehabForm::on_lineEdit_returnPressed()
{
    on_pushSearch_clicked();
}
