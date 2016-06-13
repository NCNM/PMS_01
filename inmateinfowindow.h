#ifndef INMATEINFOWINDOW_H
#define INMATEINFOWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include "database.h"
#include <QStandardPaths>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QGraphicsPixmapItem>

#define VIEW_INMATE 1
#define VIEW_OFFICER 2

namespace Ui {
class InmateInfoWindow;
}

class InmateInfoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InmateInfoWindow(QWidget *parent = 0, QString ID = 0, int record_type = 0);
    ~InmateInfoWindow();

private slots:
    void on_pushButton_clicked();

    void on_InmateInfoWindow_destroyed();

signals:
    void go_back();

private:
    Ui::InmateInfoWindow *ui;
    QSqlQueryModel * model;
    void showEvent(QShowEvent *);
};

#endif // INMATEINFOWINDOW_H
