#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    m_loginedSuccess = false;
    connected = false;
    qDebug() << "drivers: "<< QSqlDatabase::drivers();
    this_mw = NULL;
    ui->serverStatus->setStyleSheet("QLabel { background-color : white; color : red; }");
}

LoginDialog::~LoginDialog()
{
    qDebug() << "Destruct login dialog.";
    if (!m_loginedSuccess && Database::isConnected())
    {
        Database::Release();
    }
    if (this_mw)
    {
        qDebug() << "Destruct main window.";
        delete this_mw;
        this_mw = NULL;
    }
    delete ui;
}

void LoginDialog::on_pushButton_5_clicked()
{
    //This really needs to change
    if ((ui->txtID->text() == "admin") && (ui->txtPassword->text() == "admin"))
    {
        loginSuccess();
    }
    else
    {
        if (!connected) {
            QMessageBox::information(this, "Connect to database server", "No database server connection detected. You need\n"
                                                                         "to connect to a database "
                                                                         "server first before attempting to log in!\n\n"
                                                                         "PMS will now attempt to connect using default settings. If "
                                                                         "it fails, you will\nhave to manually connect to your server. "
                                                                         "To do so, click Database configuration, enter your"
                                                                         " database server's details, and then click Connect.");
            on_pushButton_connect_clicked();
        }

         QSqlDatabase db = Database::getDatabase();
         QString ID = ui->txtID->text();
         QString pass = ui->txtPassword->text();
         QString QSQuery = "SELECT * FROM ACCOUNT WHERE ID = '" + ID + "' AND PASS = '" + pass + "'";
         QSqlQuery query(db);
         query.exec(QSQuery);
         if (query.size() != 1)
         {
             QMessageBox::critical(this, "Error", "Invalid ID or password!");
             return;
         }

         //success
         query.next();
         mID = query.value(0).toString();
         loginSuccess(); 
    }
}

void LoginDialog::on_pushButton_6_clicked()
{
    this->close();
}

void LoginDialog::on_pushButton_connect_clicked()
{
    ui->serverStatus->setStyleSheet("QLabel { background-color : white; color : gray; }");
    ui->serverStatus->setText("Connecting...");

    QString hostname = ui->plainTextEdit_localhost->toPlainText();
    QString username = ui->plainTextEdit_username->toPlainText();
    QString password = ui->plainTextEdit_pass->toPlainText();
    int port = ui->plainTextEdit_port->toPlainText().toInt();

    Database *CDb = Database::init(hostname, username, password, port);

    if (CDb)
    {
        connected = true;

        ui->serverStatus->setStyleSheet("QLabel { background-color : white; color : green; }");
        ui->serverStatus->setText("Connected");

        ui->pushButton_connect->setEnabled(0);
        ui->plainTextEdit_localhost->setEnabled(0);
        ui->plainTextEdit_pass->setEnabled(0);
        ui->plainTextEdit_port->setEnabled(0);
        ui->plainTextEdit_username->setEnabled(0);
    }
    else {
        ui->serverStatus->setStyleSheet("QLabel { background-color : white; color : red; }");
        ui->serverStatus->setText("Not connected");
    }
}

void LoginDialog::loginSuccess()
{
    m_loginedSuccess = true;

    QString tmp = ui->txtID->text();
    QString IDType(2);
    IDType[0] = tmp[0];
    IDType[1] = tmp[1];
    //qDebug() << tmp;
    if (IDType == ADMIN)
    {
        this_mw = new MainWindow(ADMINTYPE, mID);
        this_mw->show();

        this->close();
    }
    else if (IDType == RELATIVE)
    {
        this_mw = new MainWindow(RELATIVETYPE, mID);
        this_mw->show();

        this->close();
    }
    else if (IDType == DINING)
    {
        this_mw = new MainWindow(DININGTYPE, mID);
        this_mw->show();

        this->close();
    }
    else if (IDType == HEALTHCARE)
    {
        this_mw = new MainWindow(HEALTHCARETYPE, mID);
        this_mw->show();

        this->close();
    }
    else if (IDType == ENTRY_RELEASE)
    {
        this_mw = new MainWindow(ENTRY_RELEASETYPE, mID);
        this_mw->show();

        this->close();
    }
    else if (IDType == REHABILITATION)
    {
        this_mw = new MainWindow(REHABILITATIONTYPE, mID);
        this_mw->show();

        this->close();
    }
    else if (IDType == MANAGE)
    {
        this_mw = new MainWindow(MANAGETYPE, mID);
        this_mw->show();

        this->close();
    }
}

void LoginDialog::on_commandLinkButton_clicked(bool checked)
{
    if (checked == true) {
        this->setMaximumSize(738, 386);
        this->setFixedSize(738, 386);
    }
    else {
        this->setMaximumSize(414, 290);
        this->setFixedSize(414, 290);
    }
}
