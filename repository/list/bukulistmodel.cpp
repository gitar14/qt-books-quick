#include "bukulistmodel.h"
#include "sqlhelper.h"

#include <QtSql>

BukuListModel::BukuListModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
}

QHash<int, QByteArray> BukuListModel::roleNames() const
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

QVariant BukuListModel::data(const QModelIndex &item, int role) const
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

void BukuListModel::refresh()
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

    if (mKategoriFilter != -1) {
        filterList.append("Buku.kd_kategori = :kategori");
        filterBinds[":kategori"] = mKategoriFilter;
    }

    if (mPenerbitFilter != -1) {
        filterList.append("Buku.kd_penerbit = :penerbit");
        filterBinds[":penerbit"] = mPenerbitFilter;
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
}

void BukuListModel::setIgnoredKodeList(QList<int> ignoredIdList)
{
    mIgnoredKodeList = ignoredIdList;
    refresh();
}

void BukuListModel::setTextQuery(const QString &newQuery)
{
    if (mTextQuery == newQuery)
        return;

    mTextQuery = newQuery;
    refresh();
}

void BukuListModel::setKategoriFilter(int newKategoriFilter)
{
    if (mKategoriFilter == newKategoriFilter)
        return;
    mKategoriFilter = newKategoriFilter;
    refresh();
}

void BukuListModel::setPenerbitFilter(int newPenerbitFilter)
{
    if (mPenerbitFilter == newPenerbitFilter)
        return;
    mPenerbitFilter = newPenerbitFilter;
    refresh();
}
