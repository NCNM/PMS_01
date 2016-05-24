#ifndef MANAGEMENTWINDOW_H
#define MANAGEMENTWINDOW_H

#include <QWidget>
#include <database.h>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class ManagementWindow;
}

class ManagementWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManagementWindow(QWidget *parent = 0);
    ~ManagementWindow();

private slots:
    void on_pushButton_16_clicked();

private:
    Ui::ManagementWindow *ui;
    QSqlTableModel *model;
};

#endif // MANAGEMENTWINDOW_H
