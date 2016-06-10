#include "inmateinfowindow.h"
#include "ui_inmateinfowindow.h"

InmateInfoWindow::InmateInfoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InmateInfoWindow)
{
    ui->setupUi(this);
}

InmateInfoWindow::~InmateInfoWindow()
{
    delete ui;
}

void InmateInfoWindow::on_pushButton_clicked()
{
    emit go_back();
    this->close();
}
