#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QTextCursor>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "database.h"
#include "mainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent, MainWindow *mw);
    ~LoginDialog();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_connect_clicked();

private:
    Ui::LoginDialog *ui;
    bool connected;
    QSqlDatabase db;
    MainWindow *this_mw;
};

#endif // LOGINDIALOG_H
