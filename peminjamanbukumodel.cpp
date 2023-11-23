#include "peminjamanbukumodel.h"
#include "basepeminjamanbukumodel.h"
#include "sqlhelper.h"
#include <QtSql>

PeminjamanBukuModel::PeminjamanBukuModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
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
    case BasePeminjamanBukuModel::DendaRole:
        columnIndex = 2;
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
                  " Peminjaman.kd_buku,"
                  " Buku.judul,"
                  " Peminjaman.denda_tambahan "
                  "FROM Peminjaman "
                  "LEFT JOIN Buku"
                  " ON Buku.kd_buku = Peminjaman.kd_buku "
                  "WHERE Peminjaman.kd_detail_peminjaman = :kode");
    query.bindValue(":kode", mKodePeminjaman);
    if (!query.exec())
        qFatal() << "Cannot query PeminjamanBukuModel " << query.lastError().text();
    setQuery(std::move(query));

    if (lastError().isValid())
        qFatal() << "Cannot set query for PeminjamanBukuModel " << lastError().text();

    emit dendaListChanged();
}

QHash<int, QByteArray> PeminjamanBukuModel::roleNames() const
{
    return BasePeminjamanBukuModel::getRoleNames();
}

void PeminjamanBukuModel::internalUpdateAll(int kodePeminjaman, QAbstractItemModel *model)
{
    QSqlQuery query;
    const int count = model->rowCount();
    for (int i = 0; i < count; i++){
        query.prepare("INSERT INTO Peminjaman("
                      " kd_detail_peminjaman,"
                      " kd_buku,"
                      " denda_tambahan"
                      ") VALUES ("
                      " :peminjaman,"
                      " :buku,"
                      " :denda"
                      ") ON CONFLICT ("
                      " kd_detail_peminjaman,"
                      " kd_buku"
                      ") DO UPDATE "
                      " SET denda_tambahan = :denda");
        QModelIndex index = model->index(i, 0);
        query.bindValue(":peminjaman", kodePeminjaman);
        query.bindValue(":buku", model->data(index, BasePeminjamanBukuModel::KodeBukuRole).toInt());
        query.bindValue(":denda", model->data(index, BasePeminjamanBukuModel::DendaRole).toInt());

        if (!query.exec())
            qFatal() << "Cannot upsert Peminjaman_buku " << query.lastError().text();
    }
}

int PeminjamanBukuModel::kodePeminjaman() const
{
    return mKodePeminjaman;
}

void PeminjamanBukuModel::setKodePeminjaman(const int &newKodePeminjaman)
{
    if (mKodePeminjaman == newKodePeminjaman)
        return;
    mKodePeminjaman = newKodePeminjaman;
    emit kodePeminjamanChanged();
    refresh();
}

void PeminjamanBukuModel::updateAll(QAbstractItemModel *model)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction())
        qFatal() << "Cannot start transaction for updateALl Pemijaman buku" << db.lastError().text();

    internalUpdateAll(mKodePeminjaman, model);

    QHash<QString, QVariant> queryBinds;

    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM"
                                 " Peminjaman "
                                 "WHERE "
                                 " kd_detail_peminjaman = :peminjaman AND"
                                 " kd_buku NOT IN (%1)")
                      .arg(SQLHelper::generateArrayBinds(
                          ":ignored_buku",
                          SQLHelper::getModelDataIntList(model, BasePeminjamanBukuModel::KodeBukuRole),
                          queryBinds
                          )));

    query.bindValue(":peminjaman", mKodePeminjaman);
    SQLHelper::applyBindMaps(query, queryBinds);

    if (!query.exec())
        qFatal() << "Deleting unused Peminjaman_buku fail " << query.lastError().text();

    if (!db.commit())
        qFatal() << "Cannot commit transaction for updateAll Peminjaman buku " << db.lastError().text();

    refresh();
}

void PeminjamanBukuModel::addAll(int kodePengadaan, QAbstractItemModel *model)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.transaction())
        qFatal() << "Start transaction to addAll Peminjaman Buku" << db.lastError().text();

    internalUpdateAll(kodePengadaan, model);

    if (!db.commit())
        qFatal() << "Cannot commit transaction for addAll Peminjaman Buku" << db.lastError().text();

    refresh();
}

void PeminjamanBukuModel::removeAll()
{
    QSqlQuery query;
    query.prepare("DELETE FROM"
                  " Peminjaman "
                  "WHERE kd_detail_peminjaman = :kode");
    query.bindValue(":kode", mKodePeminjaman);
    if (!query.exec())
        qFatal() << "Canot delete Peminjaman buku " << query.lastError().text();

    refresh();
}

void PeminjamanBukuModel::resetDenda()
{
    QSqlQuery query;
    query.prepare("UPDATE Peminjaman "
                  "SET denda_tambahan = 0 "
                  "WHERE kd_detail_peminjaman = :kode");
    query.bindValue(":kode", mKodePeminjaman);
    if (!query.exec())
        qFatal() << "Cannot reset denda for peminjaman" << query.lastError().text();

    refresh();
}

int PeminjamanBukuModel::count() const
{
    return rowCount();
}

QList<int> PeminjamanBukuModel::dendaList() const
{
    return SQLHelper::getModelDataIntList(this, BasePeminjamanBukuModel::DendaRole);
}
