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

private slots:
    void on_pushButton_HealthRecord_clicked(bool checked);

private:
    Ui::HealthcareWindow *ui;
};

#endif // HEALTHCAREWINDOW_H
