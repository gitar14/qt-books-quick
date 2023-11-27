#include "connectionmanager.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include "sqlhelper.h"
#include "repositorymanager.h"

#define CONFIG_ROOT "connection"
#define CONNECTION_KEY "rememberedDatabase"

#define MYSQL_KEY "mysql"
#define MYSQL_HOST_KEY "host"
#define MYSQL_PORT_KEY "port"
#define MYSQL_DATABASE_KEY "database"
#define MYSQL_USERNAME_KEY "username"
#define MYSQL_PASSWORD_KEY "password"
#define MYSQL_HOST_DEFAULT "localhost"
#define MYSQL_PORT_DEFAULT 3306

ConnectionManager* ConnectionManager::mInstance = nullptr;

ConnectionManager *ConnectionManager::getInstance()
{
    if (mInstance == nullptr) {
        mInstance = new ConnectionManager();
    }

    return mInstance;
}

QString ConnectionManager::getRememberedConnection()
{
    return mConfig[CONNECTION_KEY].toString();
}

void ConnectionManager::setRememberedConnection(QString db)
{
    mConfig[CONNECTION_KEY] = db;
    storeConfig();
}

QString ConnectionManager::getRememberedMySqlHost()
{
    QVariant value = mMySqlConfig[MYSQL_HOST_KEY];
    return value.isNull() ? MYSQL_HOST_DEFAULT : value.toString();
}

int ConnectionManager::getRememberedMySqlPort()
{
    QVariant value = mMySqlConfig[MYSQL_PORT_KEY];
    return value.isNull() ? MYSQL_PORT_DEFAULT : value.toInt();
}

QString ConnectionManager::getRememberedMySqlDatabase()
{
    return mMySqlConfig[MYSQL_DATABASE_KEY].toString();
}

QString ConnectionManager::getRememberedMySqlUserName()
{
    return mMySqlConfig[MYSQL_USERNAME_KEY].toString();
}

QString ConnectionManager::getRememberedMySqlPassword()
{
    return mMySqlConfig[MYSQL_PASSWORD_KEY].toString();
}

bool ConnectionManager::isMySqlConfigRemembered()
{
    return !mMySqlConfig[MYSQL_HOST_KEY].isNull() &&
           !mMySqlConfig[MYSQL_PORT_KEY].isNull() &&
           !mMySqlConfig[MYSQL_DATABASE_KEY].isNull() &&
           !mMySqlConfig[MYSQL_USERNAME_KEY].isNull() &&
           !mMySqlConfig[MYSQL_PASSWORD_KEY].isNull();
}

void ConnectionManager::openSqlite()
{
    QString dataDir = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first();
    QDir().mkdir(dataDir);

    QString dbPath = dataDir + "/data.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        emit connectionFailed(db.lastError().text());
        return;
    }

    SQLHelper::initializeDatabase(db);

    emit connected();
}

void ConnectionManager::openMySql(bool rememberConfig, QString host, int port, QString database, QString username, QString password)
{
    mMySqlConfig[MYSQL_HOST_KEY] = rememberConfig ? host : MYSQL_HOST_DEFAULT;
    mMySqlConfig[MYSQL_PORT_KEY] = rememberConfig ? port : MYSQL_PORT_DEFAULT;
    mMySqlConfig[MYSQL_DATABASE_KEY] = rememberConfig ? database : "";
    mMySqlConfig[MYSQL_USERNAME_KEY] = rememberConfig ? username : "";
    mMySqlConfig[MYSQL_PASSWORD_KEY] = rememberConfig ? password : "";
    storeConfig();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(database);
    db.setUserName(username);
    db.setPassword(password);

    if (!db.open()) {
        emit connectionFailed(db.lastError().text());
        return;
    }

    SQLHelper::initializeDatabase(db);

    emit connected();
}

bool ConnectionManager::connectByRemembered()
{
    QString connection = getRememberedConnection();

    if (connection == "mysql" && isMySqlConfigRemembered()) {
        openMySql(
            true,
            getRememberedMySqlHost(),
            getRememberedMySqlPort(),
            getRememberedMySqlDatabase(),
            getRememberedMySqlUserName(),
            getRememberedMySqlPassword()
            );
        return true;
    } else if (connection == "sqlite") {
        openSqlite();
        return true;
    }

    return false;
}

void ConnectionManager::clearRememberedConfiguration()
{
    mConfig.clear();
    mMySqlConfig.clear();
    storeConfig();
}

ConnectionManager::ConnectionManager(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getConfiguration()}
{
    loadConfig();
}

void ConnectionManager::loadConfig()
{
    mConfig = mRepository->get(CONFIG_ROOT).toMap();
    mMySqlConfig = mConfig[MYSQL_KEY].toMap();
}

void ConnectionManager::storeConfig()
{
    mConfig[MYSQL_KEY] = mMySqlConfig;
    mRepository->set(CONFIG_ROOT, mConfig);
}
