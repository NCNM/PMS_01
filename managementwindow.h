#ifndef MANAGEMENTWINDOW_H
#define MANAGEMENTWINDOW_H

#include <QWidget>
#include <database.h>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include "inmateinfowindow.h"

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

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_tableView_3_doubleClicked(const QModelIndex &index);

    void on_tableView_3_pressed(const QModelIndex &index);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_tableView_2_pressed(const QModelIndex &index);

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_pushSearch_clicked();

    void on_lineEdit_2_returnPressed();

signals:
    void row_activated(InmateInfoWindow* child, int parent);

    void send_status(QString content);

private:
    Ui::ManagementWindow *ui;
    QSqlTableModel *model;
};

#endif // MANAGEMENTWINDOW_H
