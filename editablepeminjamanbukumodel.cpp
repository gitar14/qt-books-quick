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
    case BasePeminjamanBukuModel::DendaRole:
        return item.denda;
    }

    return QVariant();
}

int EditablePeminjamanBukuModel::rowCount(const QModelIndex &parent) const
{
    return mItemList.length();
}

void EditablePeminjamanBukuModel::append(int kodeBuku)
{
    if (kodeBuku == -1) {
        qCritical() << "Cannot append blank kode buku into EditablePeminjamanBukuModel";
        return;
    }

    const int row = mItemList.length();
    emit beginInsertRows(QModelIndex(), row, row);

    Item item;
    item.kodeBuku = kodeBuku;
    item.denda = 0;

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

QList<int> EditablePeminjamanBukuModel::getKodeBukuList()
{
    return SQLHelper::getModelDataIntList(this, BasePeminjamanBukuModel::KodeBukuRole);
}

void EditablePeminjamanBukuModel::remove(int index)
{
    if (index < 0 || index > mItemList.length()) return;

    emit beginRemoveRows(QModelIndex(), index, index);

    mItemList.remove(index);

    emit endRemoveRows();

    refresh();
    emit itemsChanged();
    emit totalDendaChanged();
}

void EditablePeminjamanBukuModel::clear()
{
    emit beginRemoveRows(QModelIndex(), 0, mItemList.length());

    mItemList.clear();

    emit endRemoveRows();

    refresh();
    emit itemsChanged();
    emit totalDendaChanged();
}

void EditablePeminjamanBukuModel::populateFrom(QAbstractItemModel *model)
{
    clear();
    int count = model->rowCount();
    emit beginInsertColumns(QModelIndex(), 0, count - 1);

    for (int i = 0; i < count; i++){
        Item item;
        QModelIndex index = model->index(i, 0);
        item.kodeBuku = model->data(index, BasePeminjamanBukuModel::KodeBukuRole).toInt();
        item.judulBuku = model->data(index, BasePeminjamanBukuModel::JudulBukuRole).toString();
        item.denda = model->data(index, BasePeminjamanBukuModel::DendaRole).toInt();
        mItemList.push_back(item);
    }
    emit endInsertRows();

    refresh();
    emit itemsChanged();
    emit totalDendaChanged();
}

void EditablePeminjamanBukuModel::refresh()
{
    QString queryString = "SELECT "
                          " COUNT (kd_buku) > 0 "
                          "FROM Buku ";
    QHash<QString, QVariant> binds;
    QList<int> kodeList = getKodeBukuList();

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

bool EditablePeminjamanBukuModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    if (row < 0 || row >= mItemList.length())
        return false;

    Item& item = mItemList[row];
    if (role == BasePeminjamanBukuModel::DendaRole) {
        item.denda = value.toInt();
        emit itemsChanged();
        emit totalDendaChanged();
        return true;
    }

    return false;
}

Qt::ItemFlags EditablePeminjamanBukuModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable;
}

int EditablePeminjamanBukuModel::totalDenda() const
{
    int total = 0;
    for (int i = 0; i < mItemList.length(); i++) {
        total += mItemList.at(i).denda;
    }
    return total;
}
