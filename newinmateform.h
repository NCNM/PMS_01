#ifndef NEWINMATEFORM_H
#define NEWINMATEFORM_H

#include <QWidget>
#include "database.h"
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QStandardPaths>

namespace Ui {
class newinmateform;
}

class newinmateform : public QWidget
{
    Q_OBJECT

public:
    explicit newinmateform(QWidget *parent = 0, int purpose = 0, QString ID = 0);
    ~newinmateform();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

signals:
    void add_new_inmate(QString query);

private:
    Ui::newinmateform *ui;
    QString workingID;
    int mode;
    QSqlQueryModel *model;
    void showEvent(QShowEvent *);
};

#endif // NEWINMATEFORM_H
