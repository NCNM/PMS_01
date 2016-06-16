#include "newrehabform.h"
#include "ui_newrehabform.h"

newrehabform::newrehabform(QWidget *parent, int purpose, QString IDInm) :
    QWidget(parent),
    ui(new Ui::newrehabform)
{
    ui->setupUi(this);

    m_mode = purpose;
    workingID = IDInm;
    initID();

    if (purpose == 0)   // add new
    {
        ui->pushButton->setText("Add entry");
        ui->pushButton->setIcon(QIcon(":/images/add_new.png"));
        ui->header->setStyleSheet("QWidget #header { background-color: rgb(255, 255, 255);"
                                  "background-image: url(:/images/add_new_header.png);"
                                  "}");
    }
    else if (purpose == 1)  // update
    {
        ui->pushButton->setText("Save");
        ui->pushButton->setIcon(QIcon(":/images/save_data.png"));
        ui->header->setStyleSheet("QWidget #header { background-color: rgb(255, 255, 255);"
                                  "background-image: url(:/images/update_header.png);"
                                  "}");

        QSqlQueryModel * model = new QSqlQueryModel;
        QSqlDatabase db = Database::getDatabase();
        QString query = "SELECT * FROM REHABILITATION WHERE InmateID = '" + IDInm +"'";
        model->setQuery(query, db);


        ui->comboBox_officerInCharge->setCurrentText(model->data(model->index(0, 0)).toString());
        ui->comboBox_inmateID->addItem(model->data(model->index(0, 1)).toString());
        ui->comboBox_inmateID->setCurrentText(model->data(model->index(0, 1)).toString());
        ui->txtProgress->setText(model->data(model->index(0, 2)).toString());
        QDate tmpdate = QDate::fromString((model->data(model->index(0, 3))).toString(), "yyyy-MM-dd");
        ui->deLastUpdated->setDate(tmpdate);
        ui->txtTalents->setText(model->data(model->index(0, 4)).toString());
        ui->plainTextEdit_Recomma->setPlainText(model->data(model->index(0, 5)).toString());
        ui->lineEdit_reward->setText(model->data(model->index(0, 6)).toString());
        ui->plainTextEdit_remark->setPlainText(model->data(model->index(0, 7)).toString());
    }
}

newrehabform::~newrehabform()
{
    delete ui;
}

void newrehabform::initID()
{
    QSqlDatabase db = Database::getDatabase();
    QSqlQuery query(db);
    query.exec("SELECT * FROM INMATE WHERE ID NOT IN (SELECT InmateID FROM REHABILITATION)");

    while(query.next())
    {
        ui->comboBox_inmateID->addItem(query.value(0).toString());
    }

    query.exec("SELECT * FROM OFFICER WHERE ID LIKE 'RH%'");

    while(query.next())
    {
        ui->comboBox_officerInCharge->addItem(query.value(0).toString());
    }
}

void newrehabform::on_pushButton_clicked()
{
    QString QSQuery;
    if (m_mode == 0)
    {
        QSQuery = "INSERT `REHABILITATION` (`OfficerID`, `InmateID`, `R_level`, `Ludate`, `Talents`, `Recommendation`, `Reward`, `Remarks`) "
                  "VALUES (N'" + ui->comboBox_officerInCharge->currentText() + "', "
                  "N'" + ui->comboBox_inmateID->currentText() + "', "
                  "N'" + ui->txtProgress->text() + "', "
                  "CAST(N'" + ui->deLastUpdated->text() + "' AS Date)" + ", "
                  "N'" + ui->txtTalents->text() + "', "
                  "N'" + ui->plainTextEdit_Recomma->toPlainText() + "', "
                  "N'" + ui->lineEdit_reward->text() + "', "
                  "N'" + ui->plainTextEdit_remark->toPlainText() + "')";
    }
    else if (m_mode == 1)
    {
        QSQuery = "UPDATE REHABILITATION "
                "SET "
                "OfficerID = N'" + ui->comboBox_officerInCharge->currentText() + "', "
                "InmateID = N'" + ui->comboBox_inmateID->currentText() + "', "
                "R_level = N'" + ui->txtProgress->text() + "', "
                "Ludate = CAST(N'" + ui->deLastUpdated->text() + "' AS Date)" + ", "
                "Talents = N'" + ui->txtTalents->text() + "', "
                "Recommendation = N'" + ui->plainTextEdit_Recomma->toPlainText() + "', "
                "Reward = N'" + ui->lineEdit_reward->text() + "', "
                "Remarks = N'"  + ui->plainTextEdit_remark->toPlainText() + "' "
                "WHERE `InmateID` = N'" + workingID + "';";
    }
    emit exec_query(QSQuery);
    //query.exec(QSQuery);
    close();
}

void newrehabform::on_pushButton_cancel_clicked()
{
    close();
}
