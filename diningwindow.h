#ifndef DININGWINDOW_H
#define DININGWINDOW_H

#include <QWidget>
#include <database.h>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include "ui_diningwindow.h"
#include "inmateinfowindow.h"
#include "newmenuform.h"
#include <QDebug>

#define VIEW_INMATE 1
#define VIEW_OFFICER 2
#define VIEW_MENU 3
#define VIEW_NONE 0

namespace Ui {
class DiningWindow;
}

class DiningWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DiningWindow(QWidget *parent = 0);
    ~DiningWindow();

private slots:
    void on_pushSearch_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_viewInmates_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_Add_clicked();

    void on_pushButton_Modify_clicked();

    void exec_query(QString query);

    void on_pushButton_Menu_clicked();

    void on_Delete_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_pressed(const QModelIndex &index);

    void on_lineEdit_returnPressed();

    void on_pushButton_viewOfficers_clicked();

signals:
    void row_activated(InmateInfoWindow* child, int parent);

    void send_status(QString content);

private:
    Ui::DiningWindow *ui;
    QSqlTableModel *model;
    int curView;
};

#endif // DININGWINDOW_H
