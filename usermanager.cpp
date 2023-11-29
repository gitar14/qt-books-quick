#include "usermanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include "repositorymanager.h"
#include "usecase/userusecase.h"

UserManager::UserManager(QObject *parent)
    : QObject{parent}, mRepository{RepositoryManager::getInstance()->getUser()}
{

}

bool UserManager::hasAvailableUser()
{
    return mRepository->hasAvailableUser();
}

UserManager *UserManager::getInstance()
{
    static UserManager instance;
    return &instance;
}

UserData *UserManager::loggedUser() const
{
    return mLoggedUser;
}

void UserManager::setLoggedUser(UserData *newLoggedUser)
{
    if (mLoggedUser == newLoggedUser)
        return;
    mLoggedUser = newLoggedUser;
    mLoggedUser->setParent(this);
    emit loggedUserChanged();
}
