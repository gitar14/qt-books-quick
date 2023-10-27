#include "booklistmodel.h"

#include <QtSql>

BookListModel::BookListModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
}

QHash<int, QByteArray> BookListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[KodeRole] = "kode";
    names[JudulRole] = "judul";
    names[PenulisRole] = "penulis";
    names[TahunTerbitRole] = "tahunTerbit";
    names[KategoriRole] = "kategori";
    return names;
}

QVariant BookListModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole) return QSqlQueryModel::data(item, role);

    return data(index(item.row(), role - Qt::UserRole), Qt::DisplayRole);
}

QString BookListModel::getKodeByIndex(int index)
{
    return record(index).field(0).value().toString();
}

void BookListModel::refresh()
{
    QSqlQuery query;
    if (!query.exec("SELECT"
                    "   Buku.kd_buku,"
                    "   Buku.judul,"
                    "   Buku.penulis,"
                    "   Buku.tahun_terbit,"
                    "   Kategori.jenis "
                    "FROM Buku"
                    "   JOIN Kategori ON"
                    "       Buku.kd_kategori = Kategori.kd_kategori"))
        qFatal() << query.lastError().text();

    setQuery(std::move(query));
    if (lastError().isValid())
        qFatal() << lastError().text();
}

void BookListModel::addNew(QString judul, QString penulis, int jumlahBuku, int tahunTerbit, QString kodeKategori)
{
    QSqlQuery query;
    if (!query.exec("SELECT MAX(CAST(kd_buku AS UNSIGNED)) FROM Buku"))
        qFatal() << "Error get max id " << query.lastError();

    int maxId = -1;
    if (query.next()) {
        maxId = query.value(0).toInt();
    }

    query.prepare("INSERT INTO Buku("
                  " kd_buku,"
                  " judul,"
                  " penulis,"
                  " jumlah_buku,"
                  " tahun_terbit,"
                  " kd_kategori"
                  ") VALUES ("
                  " :kode,"
                  " :judul,"
                  " :penulis,"
                  " :jumlah,"
                  " :tahun_terbit,"
                  " :kategori"
                  ")");
    query.bindValue(":kode", QString::number(maxId + 1).rightJustified(4, '0'));
    query.bindValue(":judul", judul);
    query.bindValue(":penulis", penulis);
    query.bindValue(":jumlah", jumlahBuku);
    query.bindValue(":tahun_terbit", tahunTerbit);
    query.bindValue(":kategori", kodeKategori);

    if (!query.exec())
        qFatal() << "Cannot add Buku " << query.lastError().text();

    refresh();
}

void BookListModel::edit(QString kode, QString judul, QString penulis, int jumlahBuku, int tahunTerbit, QString kodeKategori)
{
    QSqlQuery query;
    query.prepare("UPDATE Buku SET "
                  "judul = :judul,"
                  "penulis = :penulis,"
                  "jumlah_buku = :jumlah,"
                  "tahun_terbit = :tahun_terbit,"
                  "kd_kategori = :kategori "
                  "WHERE kd_buku = :kode");
    query.bindValue(":kode", kode);
    query.bindValue(":judul", judul);
    query.bindValue(":penulis", penulis);
    query.bindValue(":jumlah", jumlahBuku);
    query.bindValue(":tahun_terbit", tahunTerbit);
    query.bindValue(":kategori", kodeKategori);

    if (!query.exec())
        qFatal() << "Cannot edit Buku " << query.lastError().text();

    refresh();
}
