#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionTest_login_triggered();

    void on_toolButton_Dashboard_clicked(bool checked);

    void on_toolButton_clicked(bool checked);

    void on_toolButton_Healthcare_clicked(bool checked);

    void on_toolButton_Dining_clicked(bool checked);

    void on_toolButton_etrr_clicked(bool checked);

    void on_toolButton_rehab_clicked(bool checked);

    void on_toolButton_mng_clicked(bool checked);

private:
    Ui::MainWindow *ui;

    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
