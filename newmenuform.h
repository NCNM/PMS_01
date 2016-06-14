#ifndef NEWMENUFORM_H
#define NEWMENUFORM_H

#include <QSqlQueryModel>
#include <QWidget>
#include <QString>
#include <QSqlDatabase>
#include "database.h"
#include <QVector>
#include <QSqlQuery>


namespace Ui {
class newmenuform;
}

class newmenuform : public QWidget
{
    Q_OBJECT

public:
    explicit newmenuform(QWidget *parent = 0, int purpose = 0, QString ID = "");
    ~newmenuform();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void exec_query(QString query);

private:
    Ui::newmenuform *ui;
    QString workingID;
    int mode;
    QSqlQueryModel *model;
};

#endif // NEWMENUFORM_H
