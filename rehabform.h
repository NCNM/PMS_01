#ifndef REHABFORM_H
#define REHABFORM_H

#include <QWidget>

namespace Ui {
class RehabForm;
}

class RehabForm : public QWidget
{
    Q_OBJECT

public:
    explicit RehabForm(QWidget *parent = 0);
    ~RehabForm();

private:
    Ui::RehabForm *ui;
};

#endif // REHABFORM_H
