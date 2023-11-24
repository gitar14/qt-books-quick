#include "textfielddata.h"

TextFieldData::TextFieldData(QObject *parent)
    : QObject{parent}
{

}

QString TextFieldData::value() const
{
    return mValue;
}

void TextFieldData::setValue(const QString &newValue)
{
    if (mValue == newValue)
        return;
    mValue = newValue;

    emit valueChanged();
    emit errorTextChanged();
    emit availableLengthChanged();
    emit isValidChanged();
}

QString TextFieldData::errorText() const
{
    if (mValue.length() == 0) return QStringLiteral("%1 tidak boleh kosong").arg(mName);
    return "";
}

int TextFieldData::maxLength() const
{
    return mMaxLength;
}

void TextFieldData::setMaxLength(int newMaxLength)
{
    if (mMaxLength == newMaxLength)
        return;
    mMaxLength = newMaxLength;

    emit maxLengthChanged();
    emit availableLengthChanged();
}

int TextFieldData::availableLength() const
{
    return mMaxLength - mValue.length();
}

QString TextFieldData::name() const
{
    return mName;
}

void TextFieldData::setName(const QString &newName)
{
    if (mName == newName)
        return;
    mName = newName;

    emit nameChanged();
    emit errorTextChanged();
}

bool TextFieldData::isValid() const
{
    return errorText().length() == 0;
}
