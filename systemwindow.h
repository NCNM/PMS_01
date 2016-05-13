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

private:
    Ui::systemwindow *ui;
};

#endif // SYSTEMWINDOW_H
