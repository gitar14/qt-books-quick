#include "pengadaanbukumodel.h"
#include "basepengadaanbukumodel.h"

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
                  " Pengadaan_buku.kd_buku,"
                  " Pengadaan_buku.jumlah_pengadaan_buku,"
                  " Buku.judul "
                  "FROM Pengadaan_buku "
                  "LEFT JOIN Buku"
                  " ON Buku.kd_buku = Pengadaan_buku.kd_buku "
                  "WHERE Pengadaan_buku.kd_pengadaan = :kode");
    query.bindValue(":kode", mKodePengadaan);
    if (!query.exec())
        qFatal() << "Cannot select Pengadaan_buku " << query.lastError().text();

    setQuery(std::move(query));

    if (lastError().isValid())
        qFatal() << "Cannot move Pengadaan_buku query " << lastError().text();

    emit countChanged();
}

QString PengadaanBukuModel::kodePengadaan() const
{
    return mKodePengadaan;
}

void PengadaanBukuModel::setKodePengadaan(const QString &newKodePengadaan)
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

    QHash<QString, QString> queryIdBinds;

    const int count = model->rowCount();
    for (int i = 0; i < count; i++) {
        queryIdBinds[QStringLiteral(":ignored_%1").arg(i)] = model->data(
            model->index(i, 0),
            BasePengadaanBukuModel::KodeBukuRole
        ).toString();
    }

    QSqlQuery query;
    query.prepare(QStringLiteral("DELETE FROM"
                                 "  Pengadaan_buku "
                                 "WHERE "
                                 " kd_pengadaan = :pengadaan AND"
                                 " kd_buku NOT IN (%1)")
                      .arg(queryIdBinds.keys().join(",")));

    query.bindValue(":pengadaan", mKodePengadaan);

    QHashIterator<QString, QString> queryIdBindsIterator(queryIdBinds);
    while (queryIdBindsIterator.hasNext()) {
        queryIdBindsIterator.next();
        query.bindValue(queryIdBindsIterator.key(), queryIdBindsIterator.value());
    }

    if (!query.exec())
        qFatal() << "Deleting unused Pengadaan_buku fail " << query.lastError().text();

    if (!db.commit())
        qFatal() << "Cannot commit transaction for updateAll Pengadaan buku " << db.lastError().text();

    refresh();
}

void PengadaanBukuModel::addAll(QString kodePengadaan, QAbstractItemModel *model)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.transaction())
        qFatal() << "Start transaction to addAll Pengadaan buku fail " << db.lastError().text();

    internalUpdateAll(kodePengadaan, model);

    if (!db.commit())
        qFatal() << "Cannot commit transaction for addAll Pengadaan buku " << db.lastError().text();
}

void PengadaanBukuModel::removeAll()
{
    QSqlQuery query;
    query.prepare("DELETE FROM"
                  " Pengadaan_buku "
                  "WHERE kd_pengadaan = :kode");
    query.bindValue(":kode", mKodePengadaan);
    if (!query.exec())
        qFatal() << "Cannot delete Pengadaan buku " << query.lastError().text();

    refresh();
}

void PengadaanBukuModel::internalUpdateAll(QString kodePengadaan, QAbstractItemModel *model)
{
    QSqlQuery query;
    const int count = model->rowCount();
    for (int i = 0; i < count; i++) {
        query.prepare("INSERT INTO Pengadaan_buku("
                      " kd_pengadaan,"
                      " kd_buku,"
                      " jumlah_pengadaan_buku"
                      ") VALUES ("
                      " :pengadaan,"
                      " :buku,"
                      " :jumlah"
                      ") ON CONFLICT ("
                      " kd_pengadaan,"
                      " kd_buku"
                      ") DO UPDATE SET "
                      " jumlah_pengadaan_buku = :jumlah");
        QModelIndex index = model->index(i, 0);
        query.bindValue(":pengadaan", kodePengadaan);
        query.bindValue(":buku", model->data(index, BasePengadaanBukuModel::KodeBukuRole).toString());
        query.bindValue(":jumlah", model->data(index, BasePengadaanBukuModel::JumlahRole).toInt());

        if (!query.exec())
            qFatal() << "Cannot upsert Pengadaan_buku " << query.lastError().text();
    }
}

int PengadaanBukuModel::count() const
{
    return rowCount();
}
