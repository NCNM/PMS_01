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
}

void ManagementWindow::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
