#include "penerbitrepository.h"
#include "sqlhelper.h"
#include <QSqlQuery>
#include <QSqlError>

PenerbitRepository::PenerbitRepository(QObject *parent)
    : QObject{parent}
{

}

QList<PenerbitData *> PenerbitRepository::getAll(QString textQuery)
{
    QHash<QString,QVariant>binds;
    QString queryString="SELECT "
                          "   kd_penerbit,"
                          "   nama_penerbit "
                          "FROM Penerbit";
    if (textQuery.length()){
        queryString+= " WHERE nama_penerbit LIKE :textQuery";
        binds[":textQuery"]="%"+textQuery+"%";

    }
    QSqlQuery query;
    query.prepare(queryString);
    SQLHelper::applyBindMaps(query,binds);
    if (!query.exec())
        qFatal() << "Cannot select from Penerbit " << query.lastError().text();

    QList<PenerbitData*> result;

    while (query.next()) {
        result.append(new PenerbitData(query.value(0).toInt(),
                                       query.value(1).toString()));
    }

    return result;
}

PenerbitDetailData *PenerbitRepository::get(int kode)
{
    QSqlQuery query;
    query.prepare("SELECT "
                  "   kd_penerbit,"
                  "   nama_penerbit,"
                  "   alamat_penerbit "
                  "FROM Penerbit "
                  "WHERE kd_penerbit = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot get Penerbit " << query.lastError().text();

    return query.next() ? new PenerbitDetailData(query.value(0).toInt(),
                                                 query.value(1).toString(),
                                                 query.value(2).toString())
                        : new PenerbitDetailData();
}

void PenerbitRepository::add(QString nama, QString alamat)
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

    emit dataChanged();
}

void PenerbitRepository::edit(int kode, QString nama, QString alamat)
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

    emit dataChanged();
}

void PenerbitRepository::remove(int kode)
{
    QSqlQuery query;
    query.prepare("DELETE from Penerbit where kd_penerbit = :kode");
    query.bindValue(":kode",kode);

    if(!query.exec())
        qFatal()<< "Cannot delete Penerbit" << query.lastError().text();

    emit dataChanged();
}
