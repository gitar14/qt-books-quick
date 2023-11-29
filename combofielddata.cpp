#include "combofielddata.h"

ComboFieldData::ComboFieldData(QObject *parent)
    : BaseFieldData{parent}
{

}

QString ComboFieldData::errorText() const
{
    if (mIndex == -1) return "tidak boleh kosong";
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
