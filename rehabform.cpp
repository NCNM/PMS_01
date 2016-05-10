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

void RehabForm::on_pushButton_16_clicked()
{
    QSqlDatabase db = Database::getDatabase();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM REHABILITATION", db);
    ui->tableView->setModel(model);
}
