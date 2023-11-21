#include "booklistdetailmodel.h"

#include <QtSql>

BookListDetailModel::BookListDetailModel(QObject *parent)
    : QObject{parent},
    mKode(-1)
{
}

int BookListDetailModel::kode()
{
    return mKode;
}

void BookListDetailModel::setKode(const int &id)
{
    this->mKode = id;
    QSqlQuery query;
    query.prepare(
        "SELECT"
        "   kd_kategori,"
        "   kd_penerbit,"
        "   jumlah_hilang "
        "FROM Buku "
        "WHERE Buku.kd_buku = :kode"
        );
    query.bindValue(":kode", mKode);

    if (!query.exec())
        qFatal() << query.lastError().text();

    if (query.next()) {
        QSqlRecord record = query.record();
        mJumlahBuku = record.value("jumlah_hilang").toInt();
        mKodeKategori = record.value("kd_kategori").toInt();
        mKodePenerbit = record.value("kd_penerbit").toInt();
    } else {
        mJumlahBuku = 0;
        mKodeKategori = -1;
        mKodePenerbit = -1;
    }
    emit kodeChanged();
}

int BookListDetailModel::jumlahBuku()
{
    return mJumlahBuku;
}

int BookListDetailModel::kodeKategori()
{
    return mKodeKategori;
}

int BookListDetailModel::kodePenerbit()
{
    return mKodePenerbit;
}
