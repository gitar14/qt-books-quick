#include "pengadaanmodel.h"
#include "basepengadaanbukumodel.h"
#include <QtSql>
#include "sqlhelper.h"
#include "usermanager.h"

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
    }

    return QSqlQueryModel::data(index(item.row(), columnIndex), Qt::DisplayRole);
}

void PengadaanModel::refresh()
{
    QHash<QString,QVariant>binds;
    QString queryString="SELECT "
                          "   kd_detail_pengadaan,"
                          "   sumber "
                          "FROM Detail_Pengadaan";
    if(mTextQuery.length() > 0){
        queryString+= " WHERE sumber LIKE :textQuery";
        binds[":textQuery"]="%"+mTextQuery+"%";
    }
    qInfo() << queryString;
    QSqlQuery query;
    query.prepare(queryString);
    SQLHelper::applyBindMaps(query,binds);

    if (!query.exec())
        qFatal() << "Cannot query Pengadaan " << query.lastError().text();

    setQuery(std::move(query));

    if (lastError().isValid())
        qFatal() << "Cannot move Pengadaan query " << lastError().text();
}

int PengadaanModel::add(QString sumber)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Detail_Pengadaan ("
                  " id_user,"
                  " sumber,"
                  " tanggal_pengadaan"
                  ") VALUES ("
                  " :user,"
                  " :sumber,"
                  " '2023-10-10'"
                  ")");
    query.bindValue(":user", UserManager::getInstance()->loggedUserId());
    query.bindValue(":sumber", sumber);

    if (!query.exec())
        qFatal() << "Cannot insert into Pengadaan " << query.lastError().text();

    refresh();

    return query.lastInsertId().toInt();
}

void PengadaanModel::update(int kode, QString sumber)
{
    QSqlQuery query;
    query.prepare("UPDATE Detail_Pengadaan "
                  " SET sumber = :sumber "
                  "WHERE "
                  " kd_detail_pengadaan = :kode"
                  );
    query.bindValue(":kode", kode);
    query.bindValue(":sumber", sumber);

    if (!query.exec())
        qFatal() << "Cannot update Pengadaan " << query.lastError().text();

    refresh();
}

void PengadaanModel::remove(int kode)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Detail_Pengadaan "
                  "WHERE kd_detail_pengadaan = :kode");
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
