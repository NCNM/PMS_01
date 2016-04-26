#include "rehabform.h"
#include "ui_rehabform.h"

RehabForm::RehabForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RehabForm)
{
    ui->setupUi(this);
}

RehabForm::~RehabForm()
{
    delete ui;
}
