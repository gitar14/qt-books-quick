#include "editablepeminjamanbukumodel.h"
#include "basepeminjamanbukumodel.h"
#include "sqlhelper.h"
#include <QtSql>

EditablePeminjamanBukuModel::EditablePeminjamanBukuModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

QVariant EditablePeminjamanBukuModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();

    if (row < 0 || row >= mItemList.length()) return QVariant();

    const Item& item = mItemList.at(row);

    switch (role) {
    case BasePeminjamanBukuModel::KodeBukuRole:
        return item.kodeBuku;
    case BasePeminjamanBukuModel::JudulBukuRole:
        return item.judulBuku;
    }

    return QVariant();
}

int EditablePeminjamanBukuModel::rowCount(const QModelIndex &parent) const
{
    return mItemList.length();
}

void EditablePeminjamanBukuModel::append(QString kodeBuku)
{
    if (kodeBuku == "") {
        qCritical() << "Cannot append blank kode buku into EditablePeminjamanBukuModel";
        return;
    }

    const int row = mItemList.length();
    emit beginInsertRows(QModelIndex(), row, row);

    Item item;
    item.kodeBuku = kodeBuku;

    QSqlQuery query;
    query.prepare("SELECT judul FROM Buku WHERE kd_buku = :kode");
    query.bindValue(":kode", kodeBuku);

    if (!query.exec())
        qFatal() << "Cannot get judul for EditablePeminjamanBukuModel " << query.lastError().text();

    if (query.next()) {
        item.judulBuku = query.record().value(0).toString();
    }

    mItemList.append(item);

    emit endInsertRows();

    refresh();
    emit itemsChanged();
}

QHash<int, QByteArray> EditablePeminjamanBukuModel::roleNames() const
{
    return BasePeminjamanBukuModel::getRoleNames();
}

QStringList EditablePeminjamanBukuModel::getKodeBukuList()
{
    QStringList list;
    QListIterator<Item> it(mItemList);
    while (it.hasNext()){
        list.append(it.next().kodeBuku);
    }
    return list;
}

void EditablePeminjamanBukuModel::remove(int index)
{
    if (index < 0 || index > mItemList.length()) return;

    emit beginRemoveRows(QModelIndex(), index, index);

    mItemList.remove(index);

    emit endRemoveRows();

    refresh();
    emit itemsChanged();
}

void EditablePeminjamanBukuModel::clear()
{
    emit beginRemoveRows(QModelIndex(), 0, mItemList.length());

    mItemList.clear();

    emit endRemoveRows();

    refresh();
    emit itemsChanged();
}

void EditablePeminjamanBukuModel::populateFrom(QAbstractItemModel *model)
{
    clear();
    int count = model->rowCount();
    emit beginInsertColumns(QModelIndex(), 0, count - 1);

    for (int i = 0; i < count; i++){
        Item item;
        QModelIndex index = model->index(i, 0);
        item.kodeBuku = model->data(index, BasePeminjamanBukuModel::KodeBukuRole).toString();
        item.judulBuku = model->data(index, BasePeminjamanBukuModel::JudulBukuRole).toString();
        mItemList.push_back(item);
    }
    emit endInsertRows();

    refresh();
    emit itemsChanged();
}

void EditablePeminjamanBukuModel::refresh()
{
    QString queryString = "SELECT "
                          " COUNT (kd_buku) > 0 "
                          "FROM Buku ";
    QHash<QString, QVariant> binds;
    QStringList kodeList = getKodeBukuList();

    if (kodeList.length() > 0) {
        queryString += QStringLiteral(" WHERE kd_buku NOT IN(%1)").arg(
            SQLHelper::generateArrayBinds(":ingored_id", kodeList, binds)
            );
    }

    QSqlQuery query;
    query.prepare(queryString);
    SQLHelper::applyBindMaps(query, binds);

    if (!query.exec())
        qFatal() << "Cannot get is buku available from EditablePeminjamanBukuModel " << query.lastError().text();

    if (query.next()) {
        mBukuAvailable = query.value(0).toBool();
        return;
    }

    mBukuAvailable = false;
}

bool EditablePeminjamanBukuModel::isBukuAvailable() const
{
    return mBukuAvailable;
}
