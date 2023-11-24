#include "penerbitmodel.h"
#include <QtSql>
#include "sqlhelper.h"

PenerbitModel::PenerbitModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
}

QHash<int, QByteArray> PenerbitModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[KodeRole] = "kode";
    names[NamaRole] = "name";
    names[AlamatRole] = "alamat";
    return names;
}

QVariant PenerbitModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(item, role);

    int columnIndex;
    switch (role) {
        case KodeRole:
        columnIndex = 0;
        break;
        case NamaRole:
        columnIndex = 1;
        break;
        case AlamatRole:
        columnIndex = 2;
        break;
        default:
        columnIndex = -1;
    }

    return QSqlQueryModel::data(index(item.row(), columnIndex), Qt::DisplayRole);
}

void PenerbitModel::refresh()
{
    QHash<QString,QVariant>binds;
    QString queryString="SELECT "
                          "   kd_penerbit,"
                          "   nama_penerbit,"
                          "   alamat_penerbit "
                          "FROM Penerbit";
    if (mTextQuery.length()){
        queryString+= " WHERE nama_penerbit LIKE :textQuery";
        binds[":textQuery"]="%"+mTextQuery+"%";

    }
    QSqlQuery query;
    query.prepare(queryString);
    SQLHelper::applyBindMaps(query,binds);
    if (!query.exec())
        qFatal() << "Cannot select from Penerbit " << query.lastError().text();

    setQuery(std::move(query));
}

void PenerbitModel::setTextQuery(const QString &newTextQuary)
{
    if (mTextQuery == newTextQuary)
        return;
    mTextQuery = newTextQuary;
    refresh();
}
