#include <QMessageBox>
#include "systemwindow.h"
#include "ui_systemwindow.h"

systemwindow::systemwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::systemwindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_16->setChecked(true);
}

systemwindow::~systemwindow()
{
    delete ui;
}

void systemwindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void systemwindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void systemwindow::on_pushButton_3_clicked()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}
