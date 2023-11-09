#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>

class UserManager : public QObject
{
    Q_OBJECT
private:
    explicit UserManager(QObject *parent = nullptr);
public:
    enum UserRole {
        AdminRole = 0,
        PegawaiRole
    };

    Q_INVOKABLE bool hasAvailableUser();
    Q_INVOKABLE void addUser(QString id, QString namaDepan, QString namaBelakang, UserRole role, QString password);
    Q_INVOKABLE void login(QString id, QString password);

    static UserManager* getInstance();
signals:
    void userAdded();
    void loggedIn();
    void loginFailed(QString reason);
};

#endif // USERMANAGER_H
