#include "entryreleaseform.h"
#include "ui_entryreleaseform.h"
#include <QDebug>

EntryReleaseForm::EntryReleaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntryReleaseForm)
{
    ui->setupUi(this);
    ui->pushSearch->setEnabled(false);
}

EntryReleaseForm::~EntryReleaseForm()
{
    delete ui;
}

void EntryReleaseForm::on_pushButton_update_clicked(bool checked)
{
    QSqlDatabase db = Database::getDatabase();
    model = new QSqlTableModel(this, db);
    model->setTable("INMATE");
    model->select();

    ui->tableView->setModel(model);

    ui->pushSearch->setEnabled(true);
}

void EntryReleaseForm::on_pushButton_3_clicked()
{
    model->select();
}

void EntryReleaseForm::on_pushButton_2_clicked()
{
    model->insertRow(model->rowCount());
}

void EntryReleaseForm::on_pushButton_clicked()
{
    model->removeRow(ui->tableView->currentIndex().row());
}

void EntryReleaseForm::on_pushSearch_clicked()
{
    QSqlDatabase db = Database::getDatabase();

    QString name = ui->lineEdit->text();
    QString query;
    query = "SELECT * FROM INMATE WHERE Firstname LIKE '%" + name + "%' OR Midname LIKE '%" + name + "%' OR Lastname LIKE '%" + name + "%'";

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query, db);
    ui->tableView->setModel(model);
}
