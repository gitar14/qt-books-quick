#include "booklistmodel.h"
#include "sqlhelper.h"

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
    names[PenerbitRole] = "penerbit";
    return names;
}

QVariant BookListModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole) return QSqlQueryModel::data(item, role);

    int columnIndex;
    switch (role){
    case KodeRole:
        columnIndex=0;
        break;
    case JudulRole:
        columnIndex=1;
        break;
    case PenulisRole:
        columnIndex=2;
        break;
    case TahunTerbitRole:
        columnIndex=3;
        break;
    case KategoriRole:
        columnIndex=4;
        break;
    case PenerbitRole:
        columnIndex=5;
        break;
    default:
        columnIndex = -1;
    }

    return data(index(item.row(), columnIndex), Qt::DisplayRole);
}

int BookListModel::getKodeByIndex(int index)
{
    return record(index).field(0).value().toInt();
}

void BookListModel::refresh()
{
    QStringList filterList;
    QHash<QString, QVariant> filterBinds;

    if (mIgnoredKodeList.length() > 0) {
        filterList.append(QString("Buku.kd_buku NOT IN (%1)").arg(
            SQLHelper::generateArrayBinds(":ignored_kode", mIgnoredKodeList, filterBinds)
        ));
    }

    if (mTextQuery.length() > 0) {
        filterList.append("Buku.judul LIKE :text_query");
        filterBinds[":text_query"] = "%" + mTextQuery + "%";
    }

    QSqlQuery query;

    QString queryString = "SELECT"
                          "   Buku.kd_buku,"
                          "   Buku.judul,"
                          "   Buku.penulis,"
                          "   Buku.tahun_terbit,"
                          "   Kategori.nama_kategori,"
                          "   Penerbit.nama_penerbit "
                          "FROM Buku"
                          "   JOIN Kategori ON"
                          "       Buku.kd_kategori = Kategori.kd_kategori "
                          "   JOIN Penerbit ON"
                          "       Penerbit.kd_penerbit = Buku.kd_penerbit ";
    if (filterList.length() > 0)
        queryString.append("WHERE ").append(filterList.join(" AND "));
    query.prepare(queryString);

    SQLHelper::applyBindMaps(query, filterBinds);

    if (!query.exec())
        qFatal() << "Cannot query for Buku " << query.lastError().text();

    setQuery(std::move(query));
    if (lastError().isValid())
        qFatal() << "Cannot set query for Buku " << lastError().text();

    emit countChanged();
}

void BookListModel::addNew(QString judul, QString penulis, int jumlahBuku, int tahunTerbit, int kodeKategori, int kodePenerbit)
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
                  " tahun_terbit,"
                  " kd_kategori,"
                  " kd_penerbit"
                  ") VALUES ("
                  " :kode,"
                  " :judul,"
                  " :penulis,"
                  " :tahun_terbit,"
                  " :kategori,"
                  " :penerbit"
                  ")");

    query.bindValue(":kode", QString::number(maxId + 1).rightJustified(4, '0'));
    query.bindValue(":judul", judul);
    query.bindValue(":penulis", penulis);
    query.bindValue(":tahun_terbit", tahunTerbit);
    query.bindValue(":kategori", kodeKategori);
    query.bindValue(":penerbit", kodePenerbit);

    if (!query.exec())
        qFatal() << "Cannot add Buku " << query.lastError().text();

    refresh();
}

void BookListModel::edit(int kode, QString judul, QString penulis, int jumlahBuku, int tahunTerbit, int kodeKategori, int kodePenerbit)
{
    QSqlQuery query;
    query.prepare("UPDATE Buku SET "
                  "judul = :judul,"
                  "penulis = :penulis,"
                  "jumlah_hilang = :jumlah,"
                  "tahun_terbit = :tahun_terbit,"
                  "kd_kategori = :kategori,"
                  "kd_penerbit = :penerbit "
                  "WHERE kd_buku = :kode");
    query.bindValue(":kode", kode);
    query.bindValue(":judul", judul);
    query.bindValue(":penulis", penulis);
    query.bindValue(":jumlah", jumlahBuku);
    query.bindValue(":tahun_terbit", tahunTerbit);
    query.bindValue(":kategori", kodeKategori);
    query.bindValue(":penerbit", kodePenerbit);

    if (!query.exec())
        qFatal() << "Cannot edit Buku " << query.lastError().text();

    refresh();
}

void BookListModel::remove(int kode)
{
    QSqlQuery query;

    query.prepare("DELETE from Buku WHERE kd_buku = :kode");
    query.bindValue(":kode", kode);
    if (!query.exec())
        qFatal() << "Cannot remove Buku " << query.lastError().text();

    refresh();
}

void BookListModel::setIgnoredKodeList(QList<int> ignoredIdList)
{
    mIgnoredKodeList = ignoredIdList;
    refresh();
}

int BookListModel::count() const
{
    return rowCount();
}

QString BookListModel::textQuery() const
{
    return mTextQuery;
}

void BookListModel::setTextQuery(const QString &newQuery)
{
    if (mTextQuery == newQuery)
        return;

    mTextQuery = newQuery;
    emit queryChanged();

    refresh();
}
