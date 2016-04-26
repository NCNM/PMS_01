#ifndef HEALTHCAREWINDOW_H
#define HEALTHCAREWINDOW_H

#include <QWidget>

namespace Ui {
class HealthcareWindow;
}

class HealthcareWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HealthcareWindow(QWidget *parent = 0);
    ~HealthcareWindow();

private:
    Ui::HealthcareWindow *ui;
};

#endif // HEALTHCAREWINDOW_H
