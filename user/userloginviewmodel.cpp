#include "userloginviewmodel.h"
#include "repositorymanager.h"
#include "usecase/userusecase.h"
#include "usermanager.h"

UserLoginViewModel::UserLoginViewModel(QObject *parent)
    : QObject{parent},
    mIdField{new TextFieldData(this)},
    mPasswordField{new TextFieldData(this)},
    mRepository{RepositoryManager::getInstance()->getUser()}
{
    mIdField->setName("ID");
    mIdField->setMaxLength(10);

    mPasswordField->setName("Password");
    mPasswordField->setMaxLength(72);

    connect(mIdField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
    connect(mPasswordField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
}

TextFieldData *UserLoginViewModel::idField() const
{
    return mIdField;
}

TextFieldData *UserLoginViewModel::passwordField() const
{
    return mPasswordField;
}

bool UserLoginViewModel::isValid() const
{
    return mIdField->isValid() && mPasswordField->isValid();
}

bool UserLoginViewModel::login()
{
    UserData* userData = mRepository->get(mIdField->value());

    if (userData->id().length() == 0) {
        mErrorText = "User tidak ada";
        emit errorTextChanged();
        delete userData;
        return false;
    }

    if (!UserUseCase::checkUserPassword(mRepository, mIdField->value(), mPasswordField->value())) {
        mErrorText = "Password salah";
        emit errorTextChanged();
        delete userData;
        return false;
    }

    UserManager::getInstance()->setLoggedUser(userData);
    return true;
}

QString UserLoginViewModel::errorText() const
{
    return mErrorText;
}
