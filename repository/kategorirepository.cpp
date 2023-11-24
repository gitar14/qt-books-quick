#include "kategorirepository.h"
#include <QSqlQuery>
#include <QSqlError>

KategoriRepository::KategoriRepository(QObject *parent) : QObject(parent)
{

}

KategoriModel *KategoriRepository::createListModel()
{
    KategoriModel* model = new KategoriModel();
    model->connect(this, SIGNAL(dataChanged()), model, SLOT(refresh()));
    return model;
}

void KategoriRepository::addNew(QString jenis)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Kategori("
                  "   nama_kategori"
                  ") VALUES ("
                  "   :kategori"
                  ")");

    query.bindValue(":kategori", jenis);

    if (!query.exec())
        qFatal() << "Cannot add Kategori " << query.lastError().text();

    emit dataChanged();
}

void KategoriRepository::edit(int kode, QString jenis)
{
    QSqlQuery query;

    query.prepare("UPDATE Kategori SET "
                  " nama_kategori = :kategori "
                  "WHERE kd_kategori = :kode");

    query.bindValue(":kode", kode);
    query.bindValue(":kategori", jenis);

    if (!query.exec())
        qFatal() << "Cannot edit Kategori " << query.lastError().text();

    emit dataChanged();
}

void KategoriRepository::remove(int kode)
{
    QSqlQuery query;

    query.prepare("DELETE FROM Kategori WHERE kd_kategori = :kode");

    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot remove Kategori " << query.lastError().text();

    emit dataChanged();
}
