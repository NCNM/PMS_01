#ifndef NEWINMATEFORM_H
#define NEWINMATEFORM_H

#include <QWidget>

namespace Ui {
class newinmateform;
}

class newinmateform : public QWidget
{
    Q_OBJECT

public:
    explicit newinmateform(QWidget *parent = 0);
    ~newinmateform();

private:
    Ui::newinmateform *ui;
};

#endif // NEWINMATEFORM_H
