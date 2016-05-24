#include "healthcarewindow.h"
#include "ui_healthcarewindow.h"
#include <QStyleFactory>
#include "database.h"
#include <QSqlQueryModel>

HealthcareWindow::HealthcareWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HealthcareWindow)
{
    ui->setupUi(this);
    ui->pushSearch->setEnabled(false);
}

HealthcareWindow::~HealthcareWindow()
{
    delete ui;
}

void HealthcareWindow::on_pushButton_HealthRecord_clicked(bool checked)
{
    /*QSqlDatabase db = Database::getDatabase();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM MEDCHECKS", db);
    ui->tableView->setModel(model);*/

    QSqlDatabase db = Database::getDatabase();
    model = new QSqlTableModel(this, db);
    model->setTable("MEDCHECKS");
    model->select();

    ui->tableView->setModel(model);

    ui->pushSearch->setEnabled(true);
}

void HealthcareWindow::on_pushAdd_clicked()
{
    model->insertRow(model->rowCount());
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
