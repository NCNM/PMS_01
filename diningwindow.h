#ifndef DININGWINDOW_H
#define DININGWINDOW_H

#include <QWidget>

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

private:
    Ui::DiningWindow *ui;
};

#endif // DININGWINDOW_H
