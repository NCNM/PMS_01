#include "database.h"
#include <QSqlError>

Database* Database::instance = NULL;

Database * Database::init(QString hostname, QString username, QString password, int port)
{
    if (instance != NULL)
        return instance;

    instance = new Database;
    instance->mDb = QSqlDatabase::addDatabase("QMYSQL");
    instance->mDb.setHostName(hostname);
    instance->mDb.setDatabaseName("pms");
    instance->mDb.setPort(port);
    instance->mDb.setUserName(username);
    instance->mDb.setPassword(password);

    if (!instance->mDb.open())
    {
        QMessageBox::critical(0,"Error", instance->mDb.lastError().text());
        delete instance;
        instance = NULL;
        return NULL;
    }
    return instance;
}

QSqlDatabase Database::getDatabase()
{
    return instance->mDb;
}

void Database::Release()
{
    instance->mDb.close();
    if (instance)
    {
        delete instance;
        instance = NULL;
    }
}
