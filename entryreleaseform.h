#ifndef ENTRYRELEASEFORM_H
#define ENTRYRELEASEFORM_H

#include <QWidget>

namespace Ui {
class EntryReleaseForm;
}

class EntryReleaseForm : public QWidget
{
    Q_OBJECT

public:
    explicit EntryReleaseForm(QWidget *parent = 0);
    ~EntryReleaseForm();

private:
    Ui::EntryReleaseForm *ui;
};

#endif // ENTRYRELEASEFORM_H
