#include "kategorifiltermodel.h"
#include "kategorimodel.h"

KategoriFilterModel::KategoriFilterModel(QObject *parent)
    : BaseFilterModel{parent}
{

}

QVariant KategoriFilterModel::getFirstData(const QModelIndex &item, int role) const
{
    switch (role) {
    case KategoriModel::KodeRole:
        return -1;
    case KategoriModel::JenisRole:
        return "Semua";
    }

    return QVariant();
}
