#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "database.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_connect_clicked();

private:
    Ui::LoginWindow *ui;
    bool connected;
    QSqlDatabase db;
};

#endif // LOGINWINDOW_H
