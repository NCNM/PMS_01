#ifndef ENTRYRELEASEFORM_H
#define ENTRYRELEASEFORM_H

#include <QWidget>
#include "database.h"
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "inmateinfowindow.h"

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

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushSearch_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_6_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void add_inmate_triggered(QString query);

signals:
    void row_activated(InmateInfoWindow* child, int parent);

private:
    Ui::EntryReleaseForm *ui;
    QSqlQueryModel *model;
};

#endif // ENTRYRELEASEFORM_H
