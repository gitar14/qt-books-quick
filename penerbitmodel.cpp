#include "penerbitmodel.h"
#include <QtSql>

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
    if (!query.exec("SELECT MAX(CAST(kd_penerbit AS UNSIGNED)) FROM Penerbit"))
        qFatal() << "Cannot get max id " << query.lastError().text();

    int maxId = -1;
    if (query.next()) {
        maxId = query.value(0).toInt();
    }

    query.prepare("INSERT INTO Penerbit("
                  " kd_penerbit,"
                  " nama_penerbit,"
                  " alamat_penerbit"
                  ") VALUES ("
                  " :kode,"
                  " :nama,"
                  " :alamat"
                  ")");

    query.bindValue(":kode", QString::number(maxId + 1).rightJustified(4, '0'));
    query.bindValue(":nama", nama);
    query.bindValue(":alamat", alamat);

    if (!query.exec())
        qFatal() << "Cannot add Penerbit " << query.lastError().text();

    refresh();
}

void PenerbitModel::edit(QString kode, QString nama, QString alamat)
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

void PenerbitModel::remove(QString kode)
{
    QSqlQuery query;
    query.prepare("DELETE from Penerbit where kd_penerbit = :kode");
    query.bindValue(":kode",kode);

    if(!query.exec())
        qFatal()<< "Cannot delete Penerbit" << query.lastError().text();

    refresh();
}

int PenerbitModel::getIndexByKode(QString kode)
{
    int count = rowCount();
    for (int i=0;i<count;i++){
        if(data(index(i,0), KodeRole).toString()== kode)
            return i;
    }
    return -1;
}

void PenerbitModel::refresh()
{
    QSqlQuery query;
    if (!query.exec("SELECT "
                    "   kd_penerbit,"
                    "   nama_penerbit,"
                    "   alamat_penerbit "
                    "FROM Penerbit"))
        qFatal() << "Cannot select from Penerbit " << query.lastError().text();

    setQuery(std::move(query));
}
