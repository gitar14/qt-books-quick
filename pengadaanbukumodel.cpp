#include "pengadaanbukumodel.h"
#include "basepengadaanbukumodel.h"
#include "sqlhelper.h"
#include <QtSql>

PengadaanBukuModel::PengadaanBukuModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
}

QHash<int, QByteArray> PengadaanBukuModel::roleNames() const
{
    return BasePengadaanBukuModel::getRoleNames();
}

QVariant PengadaanBukuModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(item, role);

    int columnIndex = -1;

    switch (role) {
    case BasePengadaanBukuModel::KodeBukuRole:
        columnIndex = 0;
        break;
    case BasePengadaanBukuModel::JumlahRole:
        columnIndex = 1;
        break;
    case BasePengadaanBukuModel::JudulBukuRole:
        columnIndex = 2;
        break;
    }

    return QSqlQueryModel::data(index(item.row(), columnIndex), Qt::DisplayRole);
}

void PengadaanBukuModel::refresh()
{
    QSqlQuery query;
    query.prepare("SELECT "
                  " Pengadaan.kd_buku,"
                  " Pengadaan.jumlah_pengadaan_buku,"
                  " Buku.judul "
                  "FROM Pengadaan "
                  "LEFT JOIN Buku"
                  " ON Buku.kd_buku = Pengadaan.kd_buku "
                  "WHERE Pengadaan.kd_detail_pengadaan = :kode");
    query.bindValue(":kode", mKodePengadaan);
    if (!query.exec())
        qFatal() << "Cannot select Pengadaan_buku " << query.lastError().text();

    setQuery(std::move(query));

    if (lastError().isValid())
        qFatal() << "Cannot move Pengadaan_buku query " << lastError().text();

    emit countChanged();
}

int PengadaanBukuModel::kodePengadaan() const
{
    return mKodePengadaan;
}

void PengadaanBukuModel::setKodePengadaan(const int &newKodePengadaan)
{
    if (mKodePengadaan == newKodePengadaan)
        return;
    mKodePengadaan = newKodePengadaan;
    refresh();
    emit kodePengadaanChanged();
}

void PengadaanBukuModel::updateAll(QAbstractItemModel *model)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction())
        qFatal() << "Cannot start transaction for updateAll Pengadaan buku " << db.lastError().text();

    internalUpdateAll(mKodePengadaan, model);

    QHash<QString, QVariant> queryBinds;

    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM"
                                 "  Pengadaan "
                                 "WHERE "
                                 " kd_detail_pengadaan = :pengadaan AND"
                                 " kd_buku NOT IN (%1)")
                      .arg(SQLHelper::generateArrayBinds(
                          ":ignored_kode",
                          SQLHelper::getModelDataIntList(model, BasePengadaanBukuModel::KodeBukuRole),
                          queryBinds
                          )));

    query.bindValue(":pengadaan", mKodePengadaan);
    SQLHelper::applyBindMaps(query, queryBinds);

    if (!query.exec())
        qFatal() << "Deleting unused Pengadaan_buku fail " << query.lastError().text();

    if (!db.commit())
        qFatal() << "Cannot commit transaction for updateAll Pengadaan buku " << db.lastError().text();

    refresh();
}

void PengadaanBukuModel::addAll(int kodePengadaan, QAbstractItemModel *model)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.transaction())
        qFatal() << "Start transaction to addAll Pengadaan buku fail " << db.lastError().text();

    internalUpdateAll(kodePengadaan, model);

    if (!db.commit())
        qFatal() << "Cannot commit transaction for addAll Pengadaan buku " << db.lastError().text();

    refresh();
}

void PengadaanBukuModel::removeAll()
{
    QSqlQuery query;
    query.prepare("DELETE FROM"
                  " Pengadaan "
                  "WHERE kd_detail_pengadaan = :kode");
    query.bindValue(":kode", mKodePengadaan);
    if (!query.exec())
        qFatal() << "Cannot delete Pengadaan buku " << query.lastError().text();

    refresh();
}

void PengadaanBukuModel::internalUpdateAll(int kodePengadaan, QAbstractItemModel *model)
{
    QSqlQuery query;
    const int count = model->rowCount();
    for (int i = 0; i < count; i++) {
        query.prepare("INSERT INTO Pengadaan("
                      " kd_detail_pengadaan,"
                      " kd_buku,"
                      " jumlah_pengadaan_buku"
                      ") VALUES ("
                      " :pengadaan,"
                      " :buku,"
                      " :jumlah"
                      ") ON CONFLICT ("
                      " kd_detail_pengadaan,"
                      " kd_buku"
                      ") DO UPDATE SET "
                      " jumlah_pengadaan_buku = :jumlah");
        QModelIndex index = model->index(i, 0);
        query.bindValue(":pengadaan", kodePengadaan);
        query.bindValue(":buku", model->data(index, BasePengadaanBukuModel::KodeBukuRole).toInt());
        query.bindValue(":jumlah", model->data(index, BasePengadaanBukuModel::JumlahRole).toInt());

        if (!query.exec())
            qFatal() << "Cannot upsert Pengadaan_buku " << query.lastError().text() << query.lastQuery() ;
    }

}

int PengadaanBukuModel::count() const
{
    return rowCount();
}
