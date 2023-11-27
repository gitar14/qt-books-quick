#include "kategorirepository.h"
#include "sqlhelper.h"
#include <QSqlQuery>
#include <QSqlError>

KategoriData::KategoriData(int kode, const QString &nama) :
    QObject(),
    mKode(kode),
    mNama(nama)
{}


int KategoriData::kode() const
{
    return mKode;
}

QString KategoriData::nama() const
{
    return mNama;
}

KategoriRepository::KategoriRepository(QObject *parent) : QObject(parent)
{

}

QList<KategoriData *> KategoriRepository::getAll(QString textQuery)
{
    QHash<QString, QVariant> bindMaps;
    QString queryString = "SELECT"
                          "   kd_kategori,"
                          "   nama_kategori "
                          "FROM Kategori";
    if (textQuery.length() > 0) {
        queryString.append(" WHERE nama_kategori LIKE :text_query");
        bindMaps[":text_query"] = "%" + textQuery + "%";
    }

    QSqlQuery query;
    query.prepare(queryString);

    SQLHelper::applyBindMaps(query, bindMaps);

    if (!query.exec())
        qFatal() << "Cannot get all kategori " << query.lastError().text();

    QList<KategoriData*> list;

    while (query.next()) {
        list.append(new KategoriData(query.value(0).toInt(), query.value(1).toString()));
    }

    return list;
}

KategoriData *KategoriRepository::get(int kode)
{
    QSqlQuery query;
    query.prepare("SELECT"
                  "   kd_kategori,"
                  "   nama_kategori "
                  "FROM Kategori "
                  "WHERE kd_kategori = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot get Kategori data " << query.lastError().text();

    return query.next() ? new KategoriData(query.value(0).toInt(), query.value(1).toString()) : new KategoriData();
}

void KategoriRepository::addNew(QString jenis)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Kategori("
                  "   nama_kategori"
                  ") VALUES ("
                  "   :kategori"
                  ")");

    query.bindValue(":kategori", jenis);

    if (!query.exec())
        qFatal() << "Cannot add Kategori " << query.lastError().text();

    emit dataChanged();
}

void KategoriRepository::edit(int kode, QString jenis)
{
    QSqlQuery query;

    query.prepare("UPDATE Kategori SET "
                  " nama_kategori = :kategori "
                  "WHERE kd_kategori = :kode");

    query.bindValue(":kode", kode);
    query.bindValue(":kategori", jenis);

    if (!query.exec())
        qFatal() << "Cannot edit Kategori " << query.lastError().text();

    emit dataChanged();
}

void KategoriRepository::remove(int kode)
{
    QSqlQuery query;

    query.prepare("DELETE FROM Kategori WHERE kd_kategori = :kode");

    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot remove Kategori " << query.lastError().text();

    emit dataChanged();
}
