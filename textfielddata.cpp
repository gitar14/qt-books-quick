#include "textfielddata.h"

TextFieldData::TextFieldData(QObject *parent)
    : BaseFieldData{parent}
{
    connect(this, SIGNAL(errorTextChanged()), this, SIGNAL(isValidChanged()));
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
}

QString TextFieldData::errorText() const
{
    if (mValue.length() == 0) return QStringLiteral("%1 tidak boleh kosong").arg(name());
    if (mReferenceField != nullptr && mReferenceField->value() != mValue)
        return QStringLiteral("%1 harus sama dengan %2").arg(name(), mReferenceField->name());
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

TextFieldData *TextFieldData::referenceField() const
{
    return mReferenceField;
}

void TextFieldData::setReferenceField(TextFieldData *newReferenceField)
{
    if (mReferenceField == newReferenceField)
        return;
    if (mReferenceField != nullptr)
        disconnect(mReferenceField, SIGNAL(valueChanged()), this, SIGNAL(errorTextChanged()));

    mReferenceField = newReferenceField;
    connect(mReferenceField, SIGNAL(valueChanged()), this, SIGNAL(errorTextChanged()));

    emit referenceFieldChanged();
    emit errorTextChanged();
}
