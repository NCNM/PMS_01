#include "entryreleaseform.h"
#include "ui_entryreleaseform.h"
#include "newinmateform.h"
#include <QDebug>

EntryReleaseForm::EntryReleaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntryReleaseForm)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    QSqlDatabase db = Database::getDatabase();
    model = new QSqlTableModel(this, db);
    model->setTable("INMATE");
    model->select();

    ui->tableView->setModel(model);

    ui->pushSearch->setEnabled(true);

    ui->pushButton_update->setChecked(true);
}

EntryReleaseForm::~EntryReleaseForm()
{
    delete ui;
}

void EntryReleaseForm::on_pushButton_3_clicked()
{
    model->select();
}

void EntryReleaseForm::on_pushButton_2_clicked()
{
    // model->insertRow(model->rowCount());
    newinmateform* nif = new newinmateform;
    nif->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    nif->show();
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

void EntryReleaseForm::on_pushButton_update_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    QSqlDatabase db = Database::getDatabase();
    model = new QSqlTableModel(this, db);
    model->setTable("INMATE");
    model->select();

    ui->tableView->setModel(model);

    ui->pushSearch->setEnabled(true);
}

void EntryReleaseForm::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void EntryReleaseForm::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void EntryReleaseForm::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void EntryReleaseForm::on_pushButton_6_clicked()
{
    ui->plainTextEdit->clear();
}
