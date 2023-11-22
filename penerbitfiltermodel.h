#ifndef PENERBITFILTERMODEL_H
#define PENERBITFILTERMODEL_H

#include "basefiltermodel.h"
#include <QQmlEngine>

class PenerbitFilterModel : public BaseFilterModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit PenerbitFilterModel(QObject *parent = nullptr);

    QVariant getFirstData(const QModelIndex &item, int role) const;
};

#endif // PENERBITFILTERMODEL_H
