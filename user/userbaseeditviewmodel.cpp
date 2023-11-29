#include "userbaseeditviewmodel.h"
#include "repositorymanager.h"

UserBaseEditViewModel::UserBaseEditViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getUser()} ,
    mIdField{new TextFieldData(this)},
    mNamaDepanField{new TextFieldData(this)},
    mNamaBelakakngField{new TextFieldData(this)},
    mPassword{new TextFieldData(this)},
    mPasswordUlang{new TextFieldData(this)}
{
    mIdField->setMaxLength(15);
    mNamaDepanField->setMaxLength(25);
    mNamaBelakakngField->setMaxLength(25);
    mPassword->setMaxLength(72);
    mPasswordUlang->setMaxLength(72);
    mPasswordUlang->setReferenceField(mPassword);

    connect(mIdField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
    connect(mNamaDepanField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
    connect(mNamaBelakakngField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
    connect(mPassword, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
    connect(mPasswordUlang, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
}


TextFieldData *UserBaseEditViewModel::idField() const
{
    return mIdField;
}

TextFieldData *UserBaseEditViewModel::namaDepanField() const
{
    return mNamaDepanField;
}

TextFieldData *UserBaseEditViewModel::namaBelakakngField() const
{
    return mNamaBelakakngField;
}

TextFieldData *UserBaseEditViewModel::password() const
{
    return mPassword;
}

TextFieldData *UserBaseEditViewModel::passwordUlang() const
{
    return mPasswordUlang;
}
