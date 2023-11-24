#include "repository/list/kategorimodel.h"
#include "sqlhelper.h"

KategoriModel::KategoriModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
}

QHash<int, QByteArray> KategoriModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[KodeRole] = "kode";
    names[JenisRole] = "jenis";
    return names;
}

QVariant KategoriModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(item, role);

    int columnIndex;
    switch (role) {
    case KodeRole:
        columnIndex = 0;
        break;
    case JenisRole:
        columnIndex = 1;
        break;
    default:
        columnIndex = -1;
    }

    return QSqlQueryModel::data(index(item.row(), columnIndex));
}

void KategoriModel::refresh()
{
    QHash<QString, QVariant> bindMaps;
    QString queryString = "SELECT"
                          "   kd_kategori,"
                          "   nama_kategori "
                          "FROM Kategori";
    if (mTextQuery.length() > 0) {
        queryString.append(" WHERE nama_kategori LIKE :text_query");
        bindMaps[":text_query"] = "%" + mTextQuery + "%";
    }

    QSqlQuery query;
    query.prepare(queryString);

    SQLHelper::applyBindMaps(query, bindMaps);

    if (!query.exec())
        qFatal("Cannot query Kategori: %s", qPrintable(query.lastError().text()));

    setQuery(std::move(query));

    if (lastError().isValid()) {
        qFatal("Cannot move Kategori query: %s", qPrintable(lastError().text()));
    }
}

void KategoriModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    refresh();
}
