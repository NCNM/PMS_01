#include "diningwindow.h"
#include "ui_diningwindow.h"
#include <database.h>
#include <QSqlTableModel>
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
    QSqlQuery qry(db);
    qry.exec("SELECT * FROM INMATE");


}
