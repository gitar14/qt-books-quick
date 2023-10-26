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
