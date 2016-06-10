#include "managementwindow.h"
#include "ui_managementwindow.h"

ManagementWindow::ManagementWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagementWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_16->setChecked(true);
}

ManagementWindow::~ManagementWindow()
{
    delete ui;
}

void ManagementWindow::on_pushButton_16_clicked()
{
/*
    QSqlDatabase db = Database::getDatabase();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM DUTY", db);
*/
    ui->stackedWidget->setCurrentIndex(0);
}

void ManagementWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void ManagementWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QSqlDatabase db = Database::getDatabase();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT ID AS ID, Lastname AS \"Last name\", Midname AS \"Middle name\", Firstname as \"First name\", "
                    "Gender AS Gender, DOB AS DOB, Hair AS \"Hair color\", Eyes AS \"Eye color\", "
                    "Eth AS \"Ethnicity\", Addr AS \"Home address\", Reason AS Reason, Custody AS Custody, "
                    "Availability AS Availability, BookIn AS Bookin, BookOut AS Bookout FROM INMATE", db);
    ui->tableView_3->setModel(model);
    ui->pushSearch->setEnabled(true);
}

void ManagementWindow::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void ManagementWindow::on_tableView_3_doubleClicked(const QModelIndex &index)
{
    QString ID = index.sibling(index.row(), 0).data().toString();
    InmateInfoWindow * inmateInfo = new InmateInfoWindow(0, ID, 1);
    emit row_activated(inmateInfo, 0);
}
