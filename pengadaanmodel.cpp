#include "pengadaanmodel.h"
#include "basepengadaanbukumodel.h"
#include <QtSql>
#include "sqlhelper.h"

PengadaanModel::PengadaanModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
}

QHash<int, QByteArray> PengadaanModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[KodeRole] = "kode";
    names[SumberRole] = "sumber";
    names[TanggalPengadaanRole] = "tanggalPengadaan";
    return names;
}

QVariant PengadaanModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(item, role);

    int columnIndex = -1;
    switch (role) {
    case KodeRole:
        columnIndex = 0;
        break;
    case SumberRole:
        columnIndex = 1;
        break;
    case TanggalPengadaanRole:
        columnIndex = 2;
        break;
    }

    return QSqlQueryModel::data(index(item.row(), columnIndex), Qt::DisplayRole);
}

void PengadaanModel::refresh()
{
    QHash<QString,QVariant>binds;
    QString queryString="SELECT "
                          "   kd_pengadaan,"
                          "   sumber,"
                          "   tanggal_pengadaan "
                          "FROM Pengadaan";
    if(mTextQuery.length() > 0){
        queryString+= " WHERE sumber LIKE :textQuery";
        binds[":textQuery"]="%"+mTextQuery+"%";
    }
    qInfo() << queryString;
    QSqlQuery query;
    query.prepare(queryString);
    SQLHelper::applyBindMaps(query,binds);

    if (!query.exec())
        qFatal() << "Cannot query Pengadaan " << query.lastError().text() << query.lastQuery();

    setQuery(std::move(query));

    if (lastError().isValid())
        qFatal() << "Cannot move Pengadaan query " << lastError().text();
}

QString PengadaanModel::add(QString sumber, QDate tanggalPengadaan)
{
    QSqlQuery query;
    if (!query.exec("SELECT MAX(CAST(kd_pengadaan AS UNSIGNED)) FROM Pengadaan"))
        qFatal() << "Cannot query max Pengadaan kode " << query.lastError().text();

    int maxKode = -1;
    if (query.next()) {
        maxKode = query.value(0).toInt();
    }

    QString kode = QString::number(maxKode + 1).rightJustified(4, '0');
    query.prepare("INSERT INTO Pengadaan ("
                  " kd_pengadaan,"
                  " sumber,"
                  " tanggal_pengadaan"
                  ") VALUES ("
                  " :kode,"
                  " :sumber,"
                  " :tanggalPengadaan"
                  ")");
    query.bindValue(":kode", kode);
    query.bindValue(":sumber", sumber);
    query.bindValue(":tanggalPengadaan", tanggalPengadaan);

    if (!query.exec())
        qFatal() << "Cannot insert into Pengadaan " << query.lastError().text();

    refresh();

    return kode;
}

void PengadaanModel::update(QString kode, QString sumber)
{
    QSqlQuery query;
    query.prepare("UPDATE Pengadaan "
                  " SET sumber = :sumber "
                  "WHERE "
                  " kd_pengadaan = :kode"
                  );
    query.bindValue(":kode", kode);
    query.bindValue(":sumber", sumber);

    if (!query.exec())
        qFatal() << "Cannot update Pengadaan " << query.lastError().text();

    refresh();
}

void PengadaanModel::remove(QString kode)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Pengadaan "
                  "WHERE kd_pengadaan = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot remove pengadaan " << query.lastError().text();

    refresh();
}

QString PengadaanModel::textQuery() const
{
    return mTextQuery;
}

void PengadaanModel::seTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    emit textQueryChanged();
    refresh ();
}
