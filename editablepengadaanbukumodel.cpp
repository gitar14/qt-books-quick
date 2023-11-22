#include "editablepengadaanbukumodel.h"
#include "basepengadaanbukumodel.h"
#include "sqlhelper.h"
#include <QtSql>

EditablePengadaanBukuModel::EditablePengadaanBukuModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

QHash<int, QByteArray>  EditablePengadaanBukuModel::roleNames() const
{
    return BasePengadaanBukuModel::getRoleNames();
}

void EditablePengadaanBukuModel::refresh()
{
    QString queryString = "SELECT "
                          " COUNT(kd_buku) > 0 "
                          "FROM Buku ";
    QHash<QString, QVariant> binds;
    QList<int> kodeList = getKodeBukuList();

    if (kodeList.length() > 0) {
        queryString += QStringLiteral(" WHERE kd_buku NOT IN(%1)").arg(
            SQLHelper::generateArrayBinds(":ignored_kode", kodeList, binds)
        );
    }

    QSqlQuery query;
    query.prepare(queryString);
    SQLHelper::applyBindMaps(query, binds);

    if (!query.exec())
        qFatal() << "Cannot get is buku available from EditablePengadaanBukuModel " << query.lastError().text();


    if (query.next()) {
        mBukuAvailable = query.record().value(0).toBool();
        return;
    }

    mBukuAvailable = false;
}


QVariant EditablePengadaanBukuModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    if (row < 0 || row > mItemList.length())
        return QVariant();

    PengadaanBukuItem item = mItemList.at(row);
    switch (role) {
    case BasePengadaanBukuModel::KodeBukuRole:
        return item.kodeBuku;
    case BasePengadaanBukuModel::JumlahRole:
        return item.jumlah;
    case BasePengadaanBukuModel::JudulBukuRole:
        return item.judulBuku;
    default:
        return QVariant();
    }
}

bool EditablePengadaanBukuModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();

    if (row < 0 || row > mItemList.length())
        return false;

    PengadaanBukuItem &item = mItemList[row];
    if (role == BasePengadaanBukuModel::JumlahRole) {
        item.jumlah = value.toInt();
        emit itemsChanged();
        return true;
    }

    return false;
}

int EditablePengadaanBukuModel::rowCount(const QModelIndex &parent) const
{
    return mItemList.length();
}

Qt::ItemFlags EditablePengadaanBukuModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable;
}

void EditablePengadaanBukuModel::append(int kodeBuku, int jumlah)
{
    if (kodeBuku == -1) {
        qCritical() << "Appending blank kodeBuku into EditablePengadaanBuku is forbidden";
        return;
    }

    int row = mItemList.length();
    emit beginInsertRows(QModelIndex(), row, row);

    PengadaanBukuItem item;
    item.kodeBuku = kodeBuku;
    item.jumlah = jumlah;

    QSqlQuery query;
    query.prepare("SELECT judul FROM Buku WHERE kd_buku = :kode");
    query.bindValue(":kode", kodeBuku);

    if (!query.exec())
        qFatal() << "Cannot get Buku detail for EditablePengaadaanBukuMode " << query.lastError().text();

    if (query.next()) {
        item.judulBuku = query.value("judul").toString();
    }

    mItemList.append(item);

    emit endInsertRows();

    refresh();
    emit itemsChanged();
}

QList<int> EditablePengadaanBukuModel::getKodeBukuList()
{
    return SQLHelper::getModelDataIntList(this, BasePengadaanBukuModel::KodeBukuRole);
}

void EditablePengadaanBukuModel::remove(int index)
{
    if (index < 0 || index > mItemList.length()) return;

    emit beginRemoveRows(QModelIndex(), index, index);

    mItemList.remove(index);

    emit endRemoveRows();

    refresh();
    emit itemsChanged();
}

void EditablePengadaanBukuModel::clear()
{
    emit beginRemoveRows(QModelIndex(), 0, mItemList.length());

    mItemList.clear();

    emit endRemoveRows();

    refresh();
    emit itemsChanged();
}

void EditablePengadaanBukuModel::populateFrom(QAbstractItemModel *model)
{
    clear();
    int count = model->rowCount();
    emit beginInsertRows(QModelIndex(), 0, count - 1);

    for (int i = 0; i < count; i++) {
        PengadaanBukuItem item;
        QModelIndex index = model->index(i, 0);
        item.kodeBuku = model->data(index, BasePengadaanBukuModel::KodeBukuRole).toInt();
        item.jumlah = model->data(index, BasePengadaanBukuModel::JumlahRole).toInt();
        item.judulBuku = model->data(index, BasePengadaanBukuModel::JudulBukuRole).toString();
        mItemList.push_back(item);
    }

    emit endInsertRows();

    refresh();
    emit itemsChanged();
}

bool EditablePengadaanBukuModel::isBukuAvailable() const
{
    return mBukuAvailable;
}
