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
        "   Buku.*,"
        "   Kategori.jenis "
        "FROM Buku "
        "   JOIN Kategori ON "
        "       Kategori.kd_kategori = Buku.kd_kategori "
        "WHERE Buku.kd_buku = :kode"
        );
    query.bindValue(":kode", mKode);

    if (!query.exec())
        qFatal() << query.lastError().text();

    if (query.next()) {
        QSqlRecord record = query.record();
        mJudul = record.value("judul").toString();
        mPenulis = record.value("penulis").toString();
        mJumlahBuku = record.value("jumlah_buku").toInt();
        mKodeKategori = record.value("kd_kategori").toString();
        mJenis = record.value("jenis").toString();
        mTahunTerbit = record.value("tahunTerbit").toInt();
    } else {
        mJudul = "";
        mPenulis = "";
        mJumlahBuku = 0;
        mKodeKategori = "";
        mJenis = "";
        mTahunTerbit = 0;
    }
    emit kodeChanged();
}

QString BookListDetailModel::judul()
{
    return mJudul;
}

QString BookListDetailModel::penulis()
{
    return mPenulis;
}

int BookListDetailModel::jumlahBuku()
{
    return mJumlahBuku;
}

QString BookListDetailModel::kodeKategori()
{
    return mKodeKategori;
}

QString BookListDetailModel::jenis()
{
    return mJenis;
}

int BookListDetailModel::tahunTerbit() const
{
    return mTahunTerbit;
}
