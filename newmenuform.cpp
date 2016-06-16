#include "newmenuform.h"
#include "ui_newmenuform.h"
#include <QDebug>

newmenuform::newmenuform(QWidget *parent, int n_mode, QString ID) :
    QWidget(parent),
    ui(new Ui::newmenuform)
{
    ui->setupUi(this);

    mode = n_mode;
    workingID = ID;

    QSqlDatabase db = Database::getDatabase();
    QSqlQuery query(db);
    query.exec("SELECT * FROM INMATE");

    while(query.next())
    {
        ui->comboBox_Subject->addItem(query.value(0).toString());
    }

    if (mode == 0)
    {
        ui->pushButton_2->setText("Add entry");
        ui->pushButton_2->setIcon(QIcon(":/images/add_new.png"));
    }
    else if (mode == 1)
    {
        ui->pushButton_2->setText("Update");
        ui->pushButton_2->setIcon(QIcon(":/images/save_data.png"));

        model = new QSqlQueryModel;
        QString query = "SELECT * FROM DINING WHERE ID = '" + ID + "'";
        model->setQuery(query, db);
        QDate tmpdate = QDate::fromString((model->data(model->index(0, 1))).toString(), "yyyy-MM-dd");
        ui->dateEdit->setDate(tmpdate);
        ui->lineEdit_Breakfast->setText(model->data(model->index(0, 2)).toString());
        ui->lineEdit_Lunch->setText(model->data(model->index(0, 3)).toString());
        ui->lineEdit_Diner->setText(model->data(model->index(0, 4)).toString());
    }
}

newmenuform::~newmenuform()
{
    delete ui;
}

QString getNewDiningID(QVector <QString> arrID)
 {
     QVector <int> arrNumID(arrID.size());

     for (int i = 0; i < arrID.size(); i++)
     {
         arrNumID[i] = QString(arrID[i].right(3)).toInt();
     }

     qSort(arrNumID.begin(), arrNumID.end());

     int i, numID;
     for (i = 1; i < arrNumID.size(); i++)
     {
         if (arrNumID[i] != arrNumID[i - 1] + 1)
             break;
     }

     if (i == arrNumID.size())
         numID = arrNumID[arrNumID.size() - 1] + 1;
     else
         numID = arrNumID[i] - 1;

     char tmp[4];
     itoa(numID, tmp, 10);
     QString newID(tmp);
     while (newID.length() < 3)
         newID = '0' + newID;
     newID = "DN" + newID;
     return newID;
 }

void newmenuform::on_pushButton_2_clicked()
{
    QSqlDatabase db = Database::getDatabase();

    // get new ID
    QVector <QString> arrID;
    QSqlQuery query(db);

    QString QSQuery = "SELECT * FROM DINING";
    query.exec(QSQuery);

    while(query.next())
    {
        arrID.push_back(query.value(0).toString());
    }

    QString newID = getNewDiningID(arrID);

    //
    if (mode == 0)
    {
        QSQuery = "INSERT INTO DINING (`ID`, `_Date`, `Breakfast`, `Lunch`, `Dinner`, "
                "`Subject`) VALUES (N'" + newID + "', CAST(N'" + ui->dateEdit->text() + "' AS Datetime)" + ", N'" + ui->lineEdit_Breakfast->text() +"', "
                "N'" + ui->lineEdit_Lunch->text() +"', N'" + ui->lineEdit_Diner->text() +"', N'" + ui->comboBox_Subject->currentText() +"');";
    }
    else if (mode == 1)
    {
        QSQuery = "UPDATE DINING "
                "SET `_Date` = CAST(N'" + ui->dateEdit->text() + "' AS Date), `Breakfast` = N'" + ui->lineEdit_Breakfast->text() +"', "
                "`Lunch` = N'" + ui->lineEdit_Lunch->text() +"', `Dinner` = N'" + ui->lineEdit_Diner->text() +"', `Subject` = N'" + ui->comboBox_Subject->currentText() +"' "
                "WHERE `ID` = N'" + workingID + "';";
    }
    emit exec_query(QSQuery);
    //query.exec(QSQuery);
    close();
}

void newmenuform::on_pushButton_3_clicked()
{
    this->close();
}
