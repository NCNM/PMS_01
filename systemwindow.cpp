#include "systemwindow.h"
#include "ui_systemwindow.h"

systemwindow::systemwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::systemwindow)
{
    ui->setupUi(this);
}

systemwindow::~systemwindow()
{
    delete ui;
}
