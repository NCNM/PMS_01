#include "newinmateform.h"
#include "ui_newinmateform.h"

newinmateform::newinmateform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newinmateform)
{
    ui->setupUi(this);
}

newinmateform::~newinmateform()
{
    delete ui;
}
