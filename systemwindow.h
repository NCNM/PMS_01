#ifndef SYSTEMWINDOW_H
#define SYSTEMWINDOW_H

#include <QWidget>

namespace Ui {
class systemwindow;
}

class systemwindow : public QWidget
{
    Q_OBJECT

public:
    explicit systemwindow(QWidget *parent = 0);
    ~systemwindow();

private slots:
    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::systemwindow *ui;
};

#endif // SYSTEMWINDOW_H
