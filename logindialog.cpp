#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent, MainWindow *mw) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this_mw = mw;
}

LoginDialog::~LoginDialog()
{
    if (Database::isConnected())
    {
        Database::Release();
    }
    delete ui;
}

void LoginDialog::on_pushButton_5_clicked()
{
    if ((ui->plainTextEdit_ID->toPlainText() == "admin") && (ui->plainTextEdit_passID->toPlainText() =="admin"))
    {
        this_mw->show();
        this->close();      // sucess
    }
    else
    {
        if (connected)
        {
            QString ID = ui->plainTextEdit_ID->toPlainText();
            QString pass = ui->plainTextEdit_passID->toPlainText();
            QString QSQuery = "SELECT * FROM ACCOUNT WHERE ID = '" + ID + "' AND PASS = '" + pass + "'";
            QSqlQuery query(db);

            qDebug() << QSQuery;

            query.exec(QSQuery);

            if (query.size() != 1)
            {
                QMessageBox::critical(this, "Error", "This ID or password does not exist!");
                return;
            }

            //succes
            this_mw->show();
            this->close();
        }
        else {
            QMessageBox::critical(this, "Error", "Please connect to server first!");
        }
    }
}

void LoginDialog::on_pushButton_6_clicked()
{
        this->close();
}

void LoginDialog::on_pushButton_connect_clicked()
{
    QString hostname = ui->plainTextEdit_localhost->toPlainText();
    QString username = ui->plainTextEdit_username->toPlainText();
    QString password = ui->plainTextEdit_pass->toPlainText();
    int port = ui->plainTextEdit_port->toPlainText().toInt();

    Database *CDb = Database::init(hostname, username, password, port);
    if (CDb)
    {
        connected = true;
        db = CDb->getDatabase();
        QMessageBox::critical(this, "Error", "Connected");
        ui->pushButton_connect->setEnabled(0);
        ui->plainTextEdit_localhost->setEnabled(0);
        ui->plainTextEdit_pass->setEnabled(0);
        ui->plainTextEdit_port->setEnabled(0);
        ui->plainTextEdit_username->setEnabled(0);
    }
}
