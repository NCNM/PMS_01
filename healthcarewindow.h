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

    void on_pushButton_19_clicked();

    void on_pushButton_17_clicked(bool checked);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_tableView_2_pressed(const QModelIndex &index);

    void on_finish_updating();

    void on_tableView_clicked(const QModelIndex &index);

signals:
    void send_status(QString content);

private:
    Ui::HealthcareWindow *ui;
    QSqlTableModel *model;
};

#endif // HEALTHCAREWINDOW_H
