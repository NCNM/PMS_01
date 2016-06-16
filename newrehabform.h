#ifndef NEWREHABFORM_H
#define NEWREHABFORM_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <database.h>

namespace Ui {
class newrehabform;
}

class newrehabform : public QWidget
{
    Q_OBJECT

public:
    explicit newrehabform(QWidget *parent = 0, int purpose = 0, QString IDInm = "");
    ~newrehabform();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_cancel_clicked();

signals:
    void exec_query(QString query);

private:
    Ui::newrehabform *ui;
    void initID();
    int m_mode;
    QString workingID;
};

#endif // NEWREHABFORM_H
