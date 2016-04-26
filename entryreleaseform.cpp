#include "entryreleaseform.h"
#include "ui_entryreleaseform.h"
#include <QDebug>

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

void EntryReleaseForm::on_pushButton_update_clicked(bool checked)
{
    QSqlDatabase db = Database::getDatabase();
    model = new QSqlTableModel(this, db);
    model->setTable("INMATE");
    model->select();

    ui->tableView->setModel(model);
}

void EntryReleaseForm::on_pushButton_3_clicked()
{
    model->select();
}

void EntryReleaseForm::on_pushButton_2_clicked()
{
    model->insertRow(model->rowCount());
}

void EntryReleaseForm::on_pushButton_clicked()
{
    model->removeRow(ui->tableView->currentIndex().row());
}
