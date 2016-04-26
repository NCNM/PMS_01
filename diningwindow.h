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

private:
    Ui::DiningWindow *ui;
};

#endif // DININGWINDOW_H
