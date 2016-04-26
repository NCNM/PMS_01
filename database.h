#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QMessageBox>
class Database
{
private:
    static Database * instance;
    static QSqlDatabase mDb;
    Database(){}


public:
    static Database * init(QString hostname, QString username, QString password, int port);
    static QSqlDatabase getDatabase();
    static void Release();
    static bool isConnected();
};


#endif // DATABASE_H

