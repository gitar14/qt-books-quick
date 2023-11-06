#include "editablepeminjamanbukumodel.h"
#include "basepeminjamanbukumodel.h"

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
}

QHash<int, QByteArray> EditablePeminjamanBukuModel::roleNames() const
{
    return BasePeminjamanBukuModel::getRoleNames();
}
