#ifndef UPDATEHEALTHFORM_H
#define UPDATEHEALTHFORM_H

#include <QWidget>
#include "diningwindow.h"

namespace Ui {
class updatehealthform;
}

class updatehealthform : public QWidget
{
    Q_OBJECT

public:
    explicit updatehealthform(QWidget *parent = 0, QString ID);
    ~updatehealthform();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::updatehealthform *ui;
    QString workingID;
};

#endif // UPDATEHEALTHFORM_H
