#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>
#include "repository/userrepository.h"

class UserManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(UserData *loggedUser READ loggedUser WRITE setLoggedUser NOTIFY loggedUserChanged FINAL)
private:
    explicit UserManager(QObject *parent = nullptr);

public:

    Q_INVOKABLE bool hasAvailableUser();

    static UserManager* getInstance();

    UserData *loggedUser() const;
    void setLoggedUser(UserData *newLoggedUser);

signals:
    void loggedUserChanged();

private:
    UserRepository* mRepository;
    UserData* mLoggedUser;
};

#endif // USERMANAGER_H
