#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QTextCursor>
#include <QMessageBox>
#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "database.h"
#include "mainwindow.h"
#include "idofficertype.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_connect_clicked();

    void loginSuccess();

    void on_commandLinkButton_clicked(bool checked);

private:
    Ui::LoginDialog *ui;
    bool connected;
    bool m_loginedSuccess;
    MainWindow *this_mw;
};

#endif // LOGINDIALOG_H
