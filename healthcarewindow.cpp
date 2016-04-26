#include "healthcarewindow.h"
#include "ui_healthcarewindow.h"
#include <QStyleFactory>
#include "database.h"
#include <QSqlQueryModel>

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

void HealthcareWindow::on_pushButton_HealthRecord_clicked(bool checked)
{
    QSqlDatabase db = Database::getDatabase();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM MEDCHECKS", db);
    ui->tableView->setModel(model);
}
