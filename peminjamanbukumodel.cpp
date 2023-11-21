#include "peminjamanbukumodel.h"
#include "basepeminjamanbukumodel.h"

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
                  " Buku.judul "
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
                      " kd_buku"
                      ") VALUES ("
                      " :peminjaman,"
                      " :buku"
                      ") ON CONFLICT ("
                      " kd_detail_peminjaman,"
                      " kd_buku"
                      ") DO NOTHING");
        QModelIndex index = model->index(i, 0);
        query.bindValue(":peminjaman", kodePeminjaman);
        query.bindValue(":buku", model->data(index, BasePeminjamanBukuModel::KodeBukuRole).toInt());

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

    QHash<QString, QString> queryIdBinds;

    const int count = model->rowCount();
    for (int i =0; i < count;i++){
        queryIdBinds[QStringLiteral(":ignored_%1").arg(i)] = model->data(
            model->index(i, 0),
            BasePeminjamanBukuModel::KodeBukuRole
        ).toString();
    }

    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM"
                                 " Peminjaman "
                                 "WHERE "
                                 " kd_detail_peminjaman = :peminjaman AND"
                                 " kd_buku NOT IN (%1)")
                      .arg(queryIdBinds.keys().join(",")));

    query.bindValue(":peminjaman", mKodePeminjaman);

    QHashIterator<QString, QString> queryIdBindsInterator(queryIdBinds);
    while (queryIdBindsInterator.hasNext()) {
        queryIdBindsInterator.next();
        query.bindValue(queryIdBindsInterator.key(), queryIdBindsInterator.value());
    }

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
}

void PeminjamanBukuModel::removeAll()
{
    QSqlQuery query;
    query.prepare("DELETE FROM"
                  " Peminjaman_buku "
                  "WHERE kd_peminjaman = :kode");
    query.bindValue(":kode", mKodePeminjaman);
    if (!query.exec())
        qFatal() << "Canot delete Peminjaman buku " << query.lastError().text();

    refresh();
}

int PeminjamanBukuModel::count() const
{
    return rowCount();
}
