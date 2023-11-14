#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>

class UserManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString loggedUserId READ loggedUserId NOTIFY loggedUserChanged)
    Q_PROPERTY(QString loggedUserName READ loggedUserName NOTIFY loggedUserChanged)
    Q_PROPERTY(UserRole loggedUserRole READ loggedUserRole NOTIFY loggedUserChanged)
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

    UserRole loggedUserRole() const;
    QString loggedUserName() const;
    QString loggedUserId() const;

private:
    UserRole mLoggedUserRole;
    QString mLoggedUserName;
    QString mLoggedUserId;

signals:
    void userAdded();
    void loggedIn();
    void loginFailed(QString reason);
    void loggedUserChanged();
};

#endif // USERMANAGER_H
