#include "pengadaanmodel.h"
#include "basepengadaanbukumodel.h"
#include <QtSql>

PengadaanModel::PengadaanModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
}

QHash<int, QByteArray> PengadaanModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[KodeRole] = "kode";
    names[SumberRole] = "sumber";
    return names;
}

QVariant PengadaanModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(item, role);

    int columnIndex = -1;
    switch (role) {
    case KodeRole:
        columnIndex = 0;
        break;
    case SumberRole:
        columnIndex = 1;
        break;
    }

    return QSqlQueryModel::data(index(item.row(), columnIndex), Qt::DisplayRole);
}

void PengadaanModel::refresh()
{
    QSqlQuery query;

    if (!query.exec("SELECT "
                    "   kd_pengadaan,"
                    "   sumber "
                    "FROM Pengadaan"))
        qFatal() << "Cannot query Pengadaan " << query.lastError().text();

    setQuery(std::move(query));

    if (lastError().isValid())
        qFatal() << "Cannot move Pengadaan query " << lastError().text();
}

QString PengadaanModel::add(QString sumber)
{
    QSqlQuery query;
    if (!query.exec("SELECT MAX(CAST(kd_pengadaan AS UNSIGNED)) FROM Pengadaan"))
        qFatal() << "Cannot query max Pengadaan kode " << query.lastError().text();

    int maxKode = -1;
    if (query.next()) {
        maxKode = query.value(0).toInt();
    }

    QString kode = QString::number(maxKode + 1).rightJustified(4, '0');
    query.prepare("INSERT INTO Pengadaan ("
                  " kd_pengadaan,"
                  " sumber"
                  ") VALUES ("
                  " :kode,"
                  " :sumber"
                  ")");
    query.bindValue(":kode", kode);
    query.bindValue(":sumber", sumber);

    if (!query.exec())
        qFatal() << "Cannot insert into Pengadaan " << query.lastError().text();

    refresh();

    return kode;
}

void PengadaanModel::update(QString kode, QString sumber)
{
    QSqlQuery query;
    query.prepare("UPDATE Pengadaan "
                  " SET sumber = :sumber "
                  "WHERE "
                  " kd_pengadaan = :kode"
                  );
    query.bindValue(":kode", kode);
    query.bindValue(":sumber", sumber);

    if (!query.exec())
        qFatal() << "Cannot update Pengadaan " << query.lastError().text();

    refresh();
}

void PengadaanModel::remove(QString kode)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Pengadaan "
                  "WHERE kd_pengadaan = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot remove pengadaan " << query.lastError().text();

    refresh();
}
