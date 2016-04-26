#include "diningwindow.h"
#include "ui_diningwindow.h"
#include <QSqlDatabase>

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
