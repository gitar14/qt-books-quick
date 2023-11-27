#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QVariantMap>
#include "repository/configurationrepository.h"

class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    static ConnectionManager* getInstance();

    Q_INVOKABLE QString getRememberedConnection();
    Q_INVOKABLE void setRememberedConnection(QString db);

    Q_INVOKABLE QString getRememberedMySqlHost();
    Q_INVOKABLE int getRememberedMySqlPort();
    Q_INVOKABLE QString getRememberedMySqlDatabase();
    Q_INVOKABLE QString getRememberedMySqlUserName();
    Q_INVOKABLE QString getRememberedMySqlPassword();
    Q_INVOKABLE bool isMySqlConfigRemembered();

    Q_INVOKABLE void openSqlite();
    Q_INVOKABLE void openMySql(
        bool rememberConfig,
        QString host,
        int port,
        QString database,
        QString username,
        QString password
        );

    Q_INVOKABLE bool connectByRemembered();
    Q_INVOKABLE void clearRememberedConfiguration();

private:
    explicit ConnectionManager(QObject *parent = nullptr);
    static ConnectionManager* mInstance;

    ConfigurationRepository* mRepository;
    QVariantMap mConfig;
    QVariantMap mMySqlConfig;

    void loadConfig();
    void storeConfig();
signals:
    void connected();
    void connectionFailed(QString message);
};

#endif // CONNECTIONMANAGER_H
