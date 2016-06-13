#ifndef HEALTHCAREWINDOW_H
#define HEALTHCAREWINDOW_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class HealthcareWindow;
}

class HealthcareWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HealthcareWindow(QWidget *parent = 0);
    ~HealthcareWindow();

private slots:

    void on_pushDelete_clicked();

    void on_pushModify_clicked();

    void on_pushSearch_clicked();

    void on_pushAccept_clicked();

    void on_pushButton_HealthRecord_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_tableView_pressed(const QModelIndex &index);

private:
    Ui::HealthcareWindow *ui;
    QSqlTableModel *model;
};

#endif // HEALTHCAREWINDOW_H
