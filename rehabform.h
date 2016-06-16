#ifndef REHABFORM_H
#define REHABFORM_H

#include <QWidget>
#include <database.h>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>
#include "newrehabform.h"

namespace Ui {
class RehabForm;
}

class RehabForm : public QWidget
{
    Q_OBJECT

public:
    explicit RehabForm(QWidget *parent = 0);
    ~RehabForm();

private slots:
    void on_pushButton_16_clicked();

    void on_pushAdd_clicked();

    void on_pushDelete_clicked();

    void on_pushModify_clicked();

    void on_pushSearch_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_tableView_pressed(const QModelIndex &index);

    void execQuery(QString query);

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::RehabForm *ui;
    QSqlQueryModel *model;

};

#endif // REHABFORM_H
