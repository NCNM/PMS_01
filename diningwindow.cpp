#include "diningwindow.h"
#include "ui_diningwindow.h"
#include <database.h>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>

DiningWindow::DiningWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiningWindow)
{
    ui->setupUi(this);
}

DiningWindow::~DiningWindow()
{
    delete ui;
}



void DiningWindow::on_pushButton_viewInmates_clicked(bool checked)
{
    QSqlDatabase db = Database::getDatabase();
/*
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("INMATE");
    model->select();
    ui->tableView->setModel(model);
*/

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM INMATE", db);
    ui->tableView->setModel(model);
}

void DiningWindow::on_pushButton_viewOfficers_clicked(bool checked)
{
    QSqlDatabase db = Database::getDatabase();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM OFFICER", db);
    ui->tableView->setModel(model);
}
