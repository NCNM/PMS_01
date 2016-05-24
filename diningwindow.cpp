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
    curView = VIEW_NONE;
    ui->pushSearch->setEnabled(false);
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

    curView = VIEW_INMATE;
    ui->pushSearch->setEnabled(true);
}

void DiningWindow::on_pushButton_viewOfficers_clicked(bool checked)
{
    QSqlDatabase db = Database::getDatabase();

    /*QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM OFFICER", db);
    ui->tableView->setModel(model);*/

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM OFFICER", db);
    ui->tableView->setModel(model);

    curView = VIEW_OFFICER;
    ui->pushSearch->setEnabled(true);
}

void DiningWindow::on_pushSearch_clicked()
{
    QSqlDatabase db = Database::getDatabase();

    QString name = ui->lineEdit->text();
    QString query;
    if (curView == VIEW_OFFICER)
    {
        query = "SELECT * FROM OFFICER WHERE Firstname LIKE '%" + name + "%' OR Midname LIKE '%" + name + "%' OR Lastname LIKE '%" + name + "%'";
    }
    else if (curView == VIEW_INMATE)
    {
        query = "SELECT * FROM INMATE WHERE Firstname LIKE '%" + name + "%' OR Midname LIKE '%" + name + "%' OR Lastname LIKE '%" + name + "%'";
    }
    else
        return;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query, db);
    ui->tableView->setModel(model);
}
