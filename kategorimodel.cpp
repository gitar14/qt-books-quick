#include "kategorimodel.h"

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

void KategoriModel::refresh()
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

void KategoriModel::addNew(QString jenis)
{
    QSqlQuery query;
    if (!query.exec("SELECT MAX(CAST(kd_kategori AS UNSIGNED)) FROM Kategori"))
        qFatal() << "Error get max id " << query.lastError();

    int maxId = -1;
    if (query.next()) {
        maxId = query.value(0).toInt();
    }

    query.prepare("INSERT INTO Kategori("
               "   kd_kategori,"
               "   jenis"
               ") VALUES ("
               "   :kode,"
               "   :jenis"
               ")");

    query.bindValue(":kode", QString::number(maxId + 1).rightJustified(4, '0'));
    query.bindValue(":jenis", jenis);

    if (!query.exec())
        qFatal() << "Cannot add Kategori " << query.lastError().text();

    refresh();
}

void KategoriModel::edit(QString kode, QString jenis)
{
    QSqlQuery query;

    query.prepare("UPDATE Kategori SET "
                  " jenis = :jenis "
                  "WHERE kd_kategori = :kode");

    query.bindValue(":kode", kode);
    query.bindValue(":jenis", jenis);

    if (!query.exec())
        qFatal() << "Cannot edit Kategori " << query.lastError().text();

    refresh();
}

void KategoriModel::remove(QString kode)
{
    QSqlQuery query;

    query.prepare("DELETE FROM Kategori WHERE kd_kategori = :kode");

    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot remove Kategori " << query.lastError().text();

    refresh();
}

int KategoriModel::getIndexByKode(QString kode)
{
    int count = rowCount();
    for (int i = 0; i < count; i++) {
        if (data(index(i, 0), KodeRole).toString() == kode) {
            return i;
        }
    }
    return -1;
}
