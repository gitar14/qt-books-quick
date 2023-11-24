#include "basefielddata.h"

BaseFieldData::BaseFieldData(QObject *parent)
    : QObject{parent}
{

}

QString BaseFieldData::name() const
{
    return mName;
}

void BaseFieldData::setName(const QString &newName)
{
    if (mName == newName)
        return;
    mName = newName;

    emit nameChanged();
    emit errorTextChanged();
}

bool BaseFieldData::isValid() const
{
    return errorText().length() == 0;
}
