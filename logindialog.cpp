#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    m_loginedSuccess = false;
    this_mw = NULL;
}

LoginDialog::~LoginDialog()
{
    qDebug() << "Destruct login dialog";
    if (!m_loginedSuccess && Database::isConnected())
    {
        Database::Release();
    }
    if (this_mw)
    {
        qDebug() << "Destruct main window";
        delete this_mw;
        this_mw = NULL;
    }
    delete ui;
}

void LoginDialog::on_pushButton_5_clicked()
{
    if ((ui->plainTextEdit_ID->toPlainText() == "admin") && (ui->plainTextEdit_passID->toPlainText() =="admin"))
    {
        loginSuccess();
    }
    else
    {
        if (connected)
        {
            QSqlDatabase db = Database::getDatabase();
            QString ID = ui->plainTextEdit_ID->toPlainText();
            QString pass = ui->plainTextEdit_passID->toPlainText();
            QString QSQuery = "SELECT * FROM ACCOUNT WHERE ID = '" + ID + "' AND PASS = '" + pass + "'";
            QSqlQuery query(db);

            query.exec(QSQuery);

            if (query.size() != 1)
            {
                QMessageBox::critical(this, "Error", "This ID or password does not exist!");
                return;
            }

            //succes
            loginSuccess();
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
        QMessageBox::critical(this, "Error", "Connected");
        ui->pushButton_connect->setEnabled(0);
        ui->plainTextEdit_localhost->setEnabled(0);
        ui->plainTextEdit_pass->setEnabled(0);
        ui->plainTextEdit_port->setEnabled(0);
        ui->plainTextEdit_username->setEnabled(0);
    }
}

void LoginDialog::loginSuccess()
{
    m_loginedSuccess = true;

    this_mw = new MainWindow;
    this_mw->show();

    this->close();
}
