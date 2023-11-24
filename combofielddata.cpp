#include "combofielddata.h"

ComboFieldData::ComboFieldData(QObject *parent)
    : BaseFieldData{parent}
{

}

QString ComboFieldData::errorText() const
{
    if (mIndex == -1) return QStringLiteral("%1 tidak boleh kosong").arg(name());
    return "";
}

int ComboFieldData::index() const
{
    return mIndex;
}

void ComboFieldData::setIndex(int newIndex)
{
    if (mIndex == newIndex)
        return;
    mIndex = newIndex;
    emit indexChanged();
    emit errorTextChanged();
    emit isValidChanged();
}
