#include "database.h"
#include <QSqlError>
#include <QDebug>

Database* Database::instance = NULL;
QSqlDatabase Database::mDb = QSqlDatabase::addDatabase(NULL);

Database * Database::init(QString hostname, QString username, QString password, int port)
{
    qDebug() << "Construct database";
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

bool Database::isConnected()
{
    return instance != NULL;
}

void Database::Release()
{
    qDebug() << "Release database";
    instance->mDb.close();
    if (instance)
    {
        delete instance;
        instance = NULL;
    }
}
