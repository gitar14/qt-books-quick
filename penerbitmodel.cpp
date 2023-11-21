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

void PenerbitModel::add(QString nama, QString alamat)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Penerbit("
                  " nama_penerbit,"
                  " alamat_penerbit"
                  ") VALUES ("
                  " :nama,"
                  " :alamat"
                  ")");

    query.bindValue(":nama", nama);
    query.bindValue(":alamat", alamat);

    if (!query.exec())
        qFatal() << "Cannot add Penerbit " << query.lastError().text();

    refresh();
}

void PenerbitModel::edit(int kode, QString nama, QString alamat)
{
    QSqlQuery query;
    query.prepare("UPDATE Penerbit SET"
                  " nama_penerbit = :nama,"
                  " alamat_penerbit = :alamat "
                  "WHERE kd_penerbit = :kode");
    query.bindValue(":nama",nama);
    query.bindValue(":alamat",alamat);
    query.bindValue(":kode",kode);

    if(!query.exec())
        qFatal()<< "Cannot edit Penerbit" << query.lastError().text();

    refresh();
}

void PenerbitModel::remove(int kode)
{
    QSqlQuery query;
    query.prepare("DELETE from Penerbit where kd_penerbit = :kode");
    query.bindValue(":kode",kode);

    if(!query.exec())
        qFatal()<< "Cannot delete Penerbit" << query.lastError().text();

    refresh();
}

int PenerbitModel::getIndexByKode(int kode)
{
    int count = rowCount();
    for (int i=0;i<count;i++){
        if(data(index(i,0), KodeRole).toInt()== kode)
            return i;
    }
    return -1;
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

QString PenerbitModel::textQuery() const
{
    return mTextQuery;
}

void PenerbitModel::setTextQuery(const QString &newTextQuary)
{
    if (mTextQuery == newTextQuary)
        return;
    mTextQuery = newTextQuary;
    emit textQueryChanged();
    refresh();
}
