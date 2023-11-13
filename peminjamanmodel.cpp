#include "peminjamanmodel.h"
#include "basepeminjamanbukumodel.h"
#include <QtSql>

PeminjamanModel::PeminjamanModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
}
QHash<int, QByteArray> PeminjamanModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[KodeRole] = "kode";
    names[TanggalRole] = "tanggal";
    names[LamaRole] = "lama";
    return names;
}

QVariant PeminjamanModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(item, role);

    int columnIndex = -1;
    switch (role) {
    case KodeRole:
        columnIndex = 0;
        break;
    case TanggalRole:
        columnIndex = 1;
        break;
    }

    return QSqlQueryModel::data(index(item.row(), columnIndex), Qt::DisplayRole);
}

void PeminjamanModel::refresh()
{
    QSqlQuery query;

    if (!query.exec("SELECT "
                    "   kd_peminjaman,"
                    "   kd_member,"
                    "   tanggal_peminjaman,"
                    "   lama_peminjaman "
                    "FROM Peminjaman"))
        qFatal() << "Cannot query Peminjaman " << query.lastError().text();

    setQuery(std::move(query));

    if (lastError().isValid())
        qFatal() << "Cannot move Peminjaman query " << lastError().text();
}

QString PeminjamanModel::add(QString sumber)
{
    QSqlQuery query;
    if (!query.exec("SELECT MAX(CAST(kd_pengadaan AS UNSIGNED)) FROM Peminjaman"))
        qFatal() << "Cannot query max Peminjaman kode " << query.lastError().text();

    int maxKode = -1;
    if (query.next()) {
        maxKode = query.value(0).toInt();
    }

    QString kode = QString::number(maxKode + 1).rightJustified(4, '0');
    query.prepare("INSERT INTO Peminjaman ("
                  " kd_peminjaman,"
                  " sumber"
                  ") VALUES ("
                  " :kode,"
                  " :sumber"
                  ")");
    query.bindValue(":kode", kode);
    query.bindValue(":sumber", sumber);

    if (!query.exec())
        qFatal() << "Cannot insert into Peminjaman " << query.lastError().text();

    refresh();

    return kode;
}

void PeminjamanModel::update(QString kode, QString sumber)
{
    QSqlQuery query;
    query.prepare("UPDATE Peminjaman "
                  " SET sumber = :sumber "
                  "WHERE "
                  " kd_peminjaman = :kode"
                  );
    query.bindValue(":kode", kode);
    query.bindValue(":sumber", sumber);

    if (!query.exec())
        qFatal() << "Cannot update Peminjaman " << query.lastError().text();

    refresh();
}

void PeminjamanModel::remove(QString kode)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Pengadaan "
                  "WHERE kd_peminjaman = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot remove peminjaman " << query.lastError().text();

    refresh();
}
