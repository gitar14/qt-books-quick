#include "kategorifiltermodel.h"

BaseFilterModel::BaseFilterModel(QObject *parent)
    : QAbstractProxyModel{parent}
{

}

int BaseFilterModel::rowCount(const QModelIndex &parent) const
{
    return sourceModel()->rowCount() + 1;
}

int BaseFilterModel::columnCount(const QModelIndex &parent) const
{
    return sourceModel()->columnCount();
}

QVariant BaseFilterModel::data(const QModelIndex &item, int role) const
{
    if (!item.isValid()) return QVariant();
    if (item.row() == 0) return getFirstData(item, role);

    return QAbstractProxyModel::data(item, role);
}

QModelIndex BaseFilterModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row > rowCount()) return QModelIndex();
    return createIndex(row, column);
}

QModelIndex BaseFilterModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

QModelIndex BaseFilterModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if (!proxyIndex.isValid() || proxyIndex.row() == 0) return QModelIndex();
    return sourceModel()->index(proxyIndex.row() - 1, proxyIndex.column());
}

QModelIndex BaseFilterModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    if (!sourceIndex.isValid() || sourceIndex.parent().isValid()) return QModelIndex();
    return createIndex(sourceIndex.row() + 1, sourceIndex.column());
}
