#include "booklistdetailmodel.h"

#include <QtSql>

BookListDetailModel::BookListDetailModel(QObject *parent)
    : QObject{parent},
    mKode("")
{
}

QString BookListDetailModel::kode()
{
    return mKode;
}

void BookListDetailModel::setKode(const QString &Id)
{
    this->mKode = Id;
    QSqlQuery query;
    query.prepare(
        "SELECT"
        "   kd_kategori,"
        "   kd_penerbit,"
        "   jumlah_buku "
        "FROM Buku "
        "WHERE Buku.kd_buku = :kode"
        );
    query.bindValue(":kode", mKode);

    if (!query.exec())
        qFatal() << query.lastError().text();

    if (query.next()) {
        QSqlRecord record = query.record();
        mJumlahBuku = record.value("jumlah_buku").toInt();
        mKodeKategori = record.value("kd_kategori").toString();
        mKodePenerbit = record.value("kd_penerbit").toString();
    } else {
        mJumlahBuku = 0;
        mKodeKategori = "";
        mKodePenerbit = "";
    }
    emit kodeChanged();
}

int BookListDetailModel::jumlahBuku()
{
    return mJumlahBuku;
}

QString BookListDetailModel::kodeKategori()
{
    return mKodeKategori;
}

QString BookListDetailModel::kodePenerbit()
{
    return mKodePenerbit;
}
