#include "connectionmanager.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include "sqlhelper.h"

ConnectionManager* ConnectionManager::mInstance = nullptr;

ConnectionManager *ConnectionManager::getInstance()
{
    if (mInstance == nullptr) {
        mInstance = new ConnectionManager();
    }

    return mInstance;
}

void ConnectionManager::openSqlite()
{
    QString dataDir = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first();
    QDir().mkdir(dataDir);

    QString dbPath = dataDir + "/data.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open())
        qFatal() << "Cannot open database " << db.lastError().text();

    SQLHelper::initializeDatabase(db);

    emit connected();
}

void ConnectionManager::openMySql(QString host, int port, QString database, QString username, QString password)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(database);
    db.setUserName(username);
    db.setPassword(password);

    if (!db.open())
        qFatal() << "Cannot open MySQL connection " << db.lastError().text();

    SQLHelper::initializeDatabase(db);

    emit connected();
}

ConnectionManager::ConnectionManager(QObject *parent)
    : QObject{parent}
{

}
