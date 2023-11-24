#include "penerbitrepository.h"
#include <QSqlQuery>
#include <QSqlError>

PenerbitRepository::PenerbitRepository(QObject *parent)
    : QObject{parent}
{

}

PenerbitModel *PenerbitRepository::createListModel()
{
    PenerbitModel* result = new PenerbitModel();
    connect(this, SIGNAL(dataChanged()), result, SLOT(refresh()));
    return result;
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
