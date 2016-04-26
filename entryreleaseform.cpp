#include "entryreleaseform.h"
#include "ui_entryreleaseform.h"

EntryReleaseForm::EntryReleaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntryReleaseForm)
{
    ui->setupUi(this);
}

EntryReleaseForm::~EntryReleaseForm()
{
    delete ui;
}
