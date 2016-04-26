#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QWidget>

namespace Ui {
class DashboardWindow;
}

class DashboardWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardWindow(QWidget *parent = 0);
    ~DashboardWindow();

private:
    Ui::DashboardWindow *ui;
};

#endif // DASHBOARDWINDOW_H
