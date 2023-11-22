#ifndef KATEGORIFILTERMODEL_H
#define KATEGORIFILTERMODEL_H

#include "basefiltermodel.h"
#include <QQmlEngine>

class KategoriFilterModel : public BaseFilterModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit KategoriFilterModel(QObject *parent = nullptr);

    QVariant getFirstData(const QModelIndex &item, int role) const;
};

#endif // KATEGORIFILTERMODEL_H
