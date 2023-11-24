#include "penerbitfiltermodel.h"
#include "repository/list/penerbitmodel.h"

PenerbitFilterModel::PenerbitFilterModel(QObject *parent)
    : BaseFilterModel{parent}
{

}

QVariant PenerbitFilterModel::getFirstData(const QModelIndex &item, int role) const
{
    switch (role) {
    case PenerbitModel::KodeRole:
        return -1;
    case PenerbitModel::NamaRole:
        return "Semua";
    }

    return QVariant();
}
