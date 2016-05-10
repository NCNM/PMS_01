#include "managementwindow.h"
#include "ui_managementwindow.h"

ManagementWindow::ManagementWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagementWindow)
{
    ui->setupUi(this);
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
}
