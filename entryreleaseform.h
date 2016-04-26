#ifndef ENTRYRELEASEFORM_H
#define ENTRYRELEASEFORM_H

#include <QWidget>
#include "database.h"
#include <QSqlTableModel>
#include <QSqlDatabase>

namespace Ui {
class EntryReleaseForm;
}

class EntryReleaseForm : public QWidget
{
    Q_OBJECT

public:
    explicit EntryReleaseForm(QWidget *parent = 0);
    ~EntryReleaseForm();

private slots:
    void on_pushButton_update_clicked(bool checked);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::EntryReleaseForm *ui;
    QSqlTableModel *model;
};

#endif // ENTRYRELEASEFORM_H
