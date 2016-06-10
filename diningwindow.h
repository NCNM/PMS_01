#ifndef DININGWINDOW_H
#define DININGWINDOW_H

#include <QWidget>
#include <QSqlTableModel>

#define VIEW_INMATE 1
#define VIEW_OFFICER 2
#define VIEW_NONE 0

namespace Ui {
class DiningWindow;
}

class DiningWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DiningWindow(QWidget *parent = 0);
    ~DiningWindow();

private slots:
    void on_pushButton_viewInmates_clicked(bool checked);
    void on_pushButton_viewOfficers_clicked(bool checked);

    void on_pushSearch_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_viewInmates_clicked();

private:
    Ui::DiningWindow *ui;
    QSqlTableModel *model;
    int curView;
};

#endif // DININGWINDOW_H
