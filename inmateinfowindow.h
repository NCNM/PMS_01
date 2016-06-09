#ifndef INMATEINFOWINDOW_H
#define INMATEINFOWINDOW_H

#include <QWidget>

namespace Ui {
class InmateInfoWindow;
}

class InmateInfoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InmateInfoWindow(QWidget *parent = 0);
    ~InmateInfoWindow();

private:
    Ui::InmateInfoWindow *ui;
};

#endif // INMATEINFOWINDOW_H
