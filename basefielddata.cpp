#include "basefielddata.h"

BaseFieldData::BaseFieldData(QObject *parent)
    : QObject{parent}
{

}

bool BaseFieldData::isValid() const
{
    return errorText().length() == 0;
}
