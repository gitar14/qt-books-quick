#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>

class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    static ConnectionManager* getInstance();

    Q_INVOKABLE void openSqlite();
    Q_INVOKABLE void openMySql(
        QString host,
        int port,
        QString database,
        QString username,
        QString password
        );


private:
    explicit ConnectionManager(QObject *parent = nullptr);
    static ConnectionManager* mInstance;

signals:
    void connected();
};

#endif // CONNECTIONMANAGER_H
