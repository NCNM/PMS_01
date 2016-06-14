#include "newrehabform.h"
#include "ui_newrehabform.h"

newrehabform::newrehabform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newrehabform)
{
    ui->setupUi(this);
}

newrehabform::~newrehabform()
{
    delete ui;
}
