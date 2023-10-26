#include "kategorimodel.h"

KategoriModel::KategoriModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    QSqlQuery query;
    if (!query.exec("SELECT"
                    "   kd_kategori,"
                    "   jenis "
                    "FROM Kategori"))
        qFatal("Cannot query Kategori: %s", qPrintable(query.lastError().text()));

    setQuery(std::move(query));

    if (lastError().isValid()) {
        qFatal("Cannot move Kategori query: %s", qPrintable(lastError().text()));
    }
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
    QVariant value;

    if (item.isValid()) {
        if (role < Qt::UserRole) {
            value = QSqlQueryModel::data(item, role);
        } else {
            int columnIdx = role - Qt::UserRole;
            QModelIndex modelIndex = this->index(item.row(), columnIdx);
            value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        }
    }
    return value;
}
