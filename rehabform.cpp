#include "rehabform.h"
#include "ui_rehabform.h"

RehabForm::RehabForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RehabForm)
{
    ui->setupUi(this);
    ui->pushSearch->setEnabled(false);
}

RehabForm::~RehabForm()
{
    delete ui;
}

void RehabForm::on_pushButton_16_clicked()
{
    /*QSqlDatabase db = Database::getDatabase();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM REHABILITATION", db);
    ui->tableView->setModel(model);*/

    QSqlDatabase db = Database::getDatabase();
    model = new QSqlTableModel(this, db);
    model->setTable("REHABILITATION");
    model->select();

    ui->tableView->setModel(model);

    ui->pushSearch->setEnabled(true);
}

void RehabForm::on_pushAdd_clicked()
{
    model->insertRow(model->rowCount());
}

void RehabForm::on_pushDelete_clicked()
{
    model->removeRow(ui->tableView->currentIndex().row());
}

void RehabForm::on_pushModify_clicked()
{
    model->select();
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
