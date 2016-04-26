#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QMessageBox>
class Database
{
private:
    static Database * instance;
    Database(){}
public:
    static Database * init(QString hostname, QString username, QString password, int port);
    QSqlDatabase getDatabase();
    QSqlDatabase mDb;
    void Release();
};


#endif // DATABASE_H

