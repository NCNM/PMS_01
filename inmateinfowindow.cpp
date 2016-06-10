#include "inmateinfowindow.h"
#include "ui_inmateinfowindow.h"
#include "mainwindow.h"

InmateInfoWindow::InmateInfoWindow(QWidget *parent, QString ID, int record_type) :
    QWidget(parent),
    ui(new Ui::InmateInfoWindow)
{
    ui->setupUi(this);
    ui->lblID->setText("Record ID: " + ID);
    QSqlDatabase db = Database::getDatabase();
    QString query;
    QSqlQueryModel *model = new QSqlQueryModel;
    if (record_type == VIEW_INMATE) {
        query = "SELECT * FROM INMATE WHERE ID = '" + ID + "'";
        model->setQuery(query, db);
        ui->txtFirstName->setText((model->data(model->index(0, 2)).toString()));
        ui->txtMidName->setText((model->data(model->index(0, 3)).toString()));
        ui->txtLastName->setText((model->data(model->index(0, 4)).toString()));
        ui->txtGender->setText((model->data(model->index(0, 5)).toString()));
        ui->txtDOB->setText((model->data(model->index(0, 6)).toString()));
        ui->txtAddress->setText((model->data(model->index(0, 7)).toString()));
        ui->txtEth->setText((model->data(model->index(0, 8)).toString()));
        ui->txtEyes->setText((model->data(model->index(0, 9)).toString()));
        ui->txtHair->setText((model->data(model->index(0, 10)).toString()));
        ui->txtReason->setText((model->data(model->index(0, 11)).toString()));
        ui->txtCustody->setText((model->data(model->index(0, 12)).toString()));
        ui->txtAvaialable->setText(model->data(model->index(0, 13)).toString());
    }
    else if (record_type == VIEW_OFFICER) {
        query = "SELECT * FROM OFFICER WHERE ID = '" + ID + "'";
        model->setQuery(query, db);
        ui->txtFirstName->setText((model->data(model->index(0, 1)).toString()));
        ui->txtMidName->setText((model->data(model->index(0, 2)).toString()));
        ui->txtLastName->setText((model->data(model->index(0, 3)).toString()));
        ui->txtGender->setText((model->data(model->index(0, 4)).toString()));
        ui->txtDOB->setText((model->data(model->index(0, 5)).toString()));
        ui->txtAddress->setText((model->data(model->index(0, 6)).toString()));
        ui->txtEth->setText((model->data(model->index(0, 7)).toString()));
        ui->label_7->setText("Phone: ");
    }
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

void InmateInfoWindow::on_InmateInfoWindow_destroyed()
{

}
