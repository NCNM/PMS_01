#ifndef REHABFORM_H
#define REHABFORM_H

#include <QWidget>
#include <database.h>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>

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

private:
    Ui::RehabForm *ui;
};

#endif // REHABFORM_H
