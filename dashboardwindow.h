#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QWidget>
#include <database.h>
#include <QDebug>
#include <QSqlQueryModel>
#include "inmateinfowindow.h"
#include <QModelIndexList>
#include <QModelIndex>

namespace Ui {
class DashboardWindow;
}

class DashboardWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardWindow(QWidget *parent = 0, bool isRelative = false, QString ID = "");
    ~DashboardWindow();

private slots:
    void on_pushButton_connect_clicked();
    void on_pushButton_connect_2_clicked();

    void on_pushButton_overview_clicked();

    void on_pushButton_connect_3_clicked();

signals:
    void row_activated(InmateInfoWindow* child, int parent);
private:
    Ui::DashboardWindow *ui;
    QString m_RelativeID; // use for relative
    QString m_InmateID;
};

#endif // DASHBOARDWINDOW_H
