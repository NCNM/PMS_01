#ifndef NEWREHABFORM_H
#define NEWREHABFORM_H

#include <QWidget>

namespace Ui {
class newrehabform;
}

class newrehabform : public QWidget
{
    Q_OBJECT

public:
    explicit newrehabform(QWidget *parent = 0);
    ~newrehabform();

private:
    Ui::newrehabform *ui;
};

#endif // NEWREHABFORM_H
