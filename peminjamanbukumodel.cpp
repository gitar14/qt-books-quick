#include "peminjamanbukumodel.h"
#include "basepeminjamanbukumodel.h"

#include <QtSql>

PeminjamanBukuModel::PeminjamanBukuModel(QObject *parent)
    : QSqlQueryModel{parent}
{

}

QVariant PeminjamanBukuModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole) return QSqlQueryModel::data(item, role);

    int columnIndex;
    switch (role) {
    case BasePeminjamanBukuModel::KodeBukuRole:
        columnIndex = 0;
        break;
    case BasePeminjamanBukuModel::JudulBukuRole:
        columnIndex = 1;
        break;
    default:
        columnIndex = -1;
    }

    return QSqlQueryModel::data(index(item.row(), columnIndex), Qt::DisplayRole);
}

void PeminjamanBukuModel::refresh()
{
    QSqlQuery query;
    query.prepare("SELECT"
                  " Peminjaman_buku.kd_buku,"
                  " Peminjaman_buku.judul "
                  "FROM Peminjaman_buku "
                  "LEFT JOIN Buku"
                  " ON Buku.kd_buku = Peminjaman_buku.kd_buku "
                  "WHERE Peminjaman_buku.kd_peminjaman = :kode");
    query.bindValue(":kode", mKodePeminjaman);
    if (!query.exec())
        qFatal() << "Cannot query PeminjamanBukuModel " << query.lastError().text();

    setQuery(std::move(query));

    if (lastError().isValid())
        qFatal() << "Cannot set query for PeminjamanBukuModel " << lastError().text();
}

QHash<int, QByteArray> PeminjamanBukuModel::roleNames() const
{
    return BasePeminjamanBukuModel::getRoleNames();
}

void PeminjamanBukuModel::internalUpdateAll(QString kodePeminjaman, QAbstractItemModel *model)
{
    
}

QString PeminjamanBukuModel::kodePeminjaman() const
{
    return mKodePeminjaman;
}

void PeminjamanBukuModel::setKodePeminjaman(const QString &newKodePeminjaman)
{
    if (mKodePeminjaman == newKodePeminjaman)
        return;
    mKodePeminjaman = newKodePeminjaman;
    emit kodePeminjamanChanged();
    refresh();
}

void PeminjamanBukuModel::updateAll(QAbstractItemModel *model)
{
    
}

void PeminjamanBukuModel::addAll(QString kodePengadaan, QAbstractItemModel *model)
{
    
}

void PeminjamanBukuModel::removeAll()
{
    
}

int PeminjamanBukuModel::count() const
{
    
}
