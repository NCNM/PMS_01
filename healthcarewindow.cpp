#include "healthcarewindow.h"
#include "ui_healthcarewindow.h"
#include <QStyleFactory>

HealthcareWindow::HealthcareWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HealthcareWindow)
{
    ui->setupUi(this);
}

HealthcareWindow::~HealthcareWindow()
{
    delete ui;
}
