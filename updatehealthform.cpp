#include "updatehealthform.h"
#include "ui_updatehealthform.h"

updatehealthform::updatehealthform(QWidget *parent, QString ID) :
    QWidget(parent),
    ui(new Ui::updatehealthform)
{
    ui->setupUi(this);
    workingID = ID;
    QSqlDatabase db = Database::getDatabase();
    QString query;
    model = new QSqlQueryModel;
    query = "SELECT * FROM MEDCHECKS WHERE ID = '" + ID + "'";
    model->setQuery(query, db);
    ui->txtID->setText(workingID);
    ui->txtID->setReadOnly(1);
    QDate tmpdate = QDate::fromString((model->data(model->index(0, 2))).toString(), "yyyy-M-dd");
    ui->deDate->setDate(tmpdate);
    ui->deDate->setReadOnly(1);
    ui->cmbUrgency->setCurrentText((model->data(model->index(0, 3)).toString()));
    ui->txtCondition->setText((model->data(model->index(0, 4)).toString()));
    ui->txtRemarks->setPlainText((model->data(model->index(0, 5)).toString()));
}

updatehealthform::~updatehealthform()
{
    delete ui;
}

void updatehealthform::on_pushButton_clicked()
{
    this->close();
}

void updatehealthform::on_pushButton_2_clicked()
{
    QString query;
    query = "UPDATE MEDCHECKS SET "
            "Urgency = '" + ui->cmbUrgency->currentText() + "', MEDCHECKS_Date = '"
            + ui->txtCondition->text() + "', Remarks = '" + ui->txtRemarks->toPlainText()
            + "' WHERE ID = '" + workingID + "'";
    QSqlQuery satan_approves;
    satan_approves.prepare(query);
    satan_approves.exec();
    this->close();
}
