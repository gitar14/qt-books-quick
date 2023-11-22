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
        mJumlahHilang = record.value("jumlah_hilang").toInt();
        mKodeKategori = record.value("kd_kategori").toInt();
        mKodePenerbit = record.value("kd_penerbit").toInt();
    } else {
        mJumlahHilang = 0;
        mKodeKategori = -1;
        mKodePenerbit = -1;
    }

    query.prepare("SELECT "
                  "SUM(jumlah_pengadaan_buku) "
                  "FROM Pengadaan "
                  "WHERE kd_buku = :kode");
    query.bindValue(":kode", mKode);

    if (!query.exec())
        qFatal() << "Cannot get jumlah pengadaan" << query.lastError().text();

    mJumlahPengadaan = query.next() ? query.value(0).toInt() : 0;

    query.prepare("SELECT "
                  "COUNT(Peminjaman.kd_peminjaman) "
                  "FROM Peminjaman "
                  "INNER JOIN Detail_Peminjaman "
                  " ON Detail_Peminjaman.kd_detail_peminjaman = Peminjaman.kd_detail_peminjaman "
                  "WHERE Peminjaman.kd_buku = :kode AND Detail_Peminjaman.tanggal_pengembalian IS NULL");
    query.bindValue(":kode", mKode);

    if (!query.exec())
        qFatal() << "Cannot get jumlah dipinjam" << query.lastError().text() << query.lastError().nativeErrorCode();

    mJumlahDipinjam = query.next() ? query.value(0).toInt() : 0;

    emit kodeChanged();
}

int BookListDetailModel::kodeKategori()
{
    return mKodeKategori;
}

int BookListDetailModel::kodePenerbit()
{
    return mKodePenerbit;
}

int BookListDetailModel::jumlahPengadaan() const
{
    return mJumlahPengadaan;
}

int BookListDetailModel::jumlahHilang() const
{
    return mJumlahHilang;
}

int BookListDetailModel::jumlahDipinjam() const
{
    return mJumlahDipinjam;
}
