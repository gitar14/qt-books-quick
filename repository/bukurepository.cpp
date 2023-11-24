#include "bukurepository.h"
#include <QSqlQuery>
#include <QSqlError>

BukuData::BukuData(int kode,
                   QString judul,
                   QString penulis,
                   int jumlahHilang,
                   int tahunTerbit,
                   int kodeKategori,
                   QString namaKategori,
                   int kodePenerbit,
                   QString namaPenerbit
                   ): QObject(),
    mKode{kode},
    mJudul{judul},
    mPenulis{penulis},
    mJumlahHilang{jumlahHilang},
    mTahunTerbit{tahunTerbit},
    mKodeKategori{kodeKategori},
    mNamaKategori{namaKategori},
    mKodePenerbit{kodePenerbit},
    mNamaPenerbit{namaPenerbit} {

}

int BukuData::kode() const
{
    return mKode;
}

QString BukuData::judul() const
{
    return mJudul;
}

QString BukuData::penulis() const
{
    return mPenulis;
}

int BukuData::jumlahHilang() const
{
    return mJumlahHilang;
}

int BukuData::tahunTerbit() const
{
    return mTahunTerbit;
}

int BukuData::kodeKategori() const
{
    return mKodeKategori;
}

QString BukuData::namaKategori() const
{
    return mNamaKategori;
}

int BukuData::kodePenebit() const
{
    return mKodePenerbit;
}

QString BukuData::namaPenerbit() const
{
    return mNamaPenerbit;
}


BukuRepository::BukuRepository(QObject *parent)
    : QObject{parent}
{

}

BukuListModel *BukuRepository::createListModel()
{
    BukuListModel* model = new BukuListModel();
    connect(this, SIGNAL(dataChanged()), model, SLOT(refresh()));
    return model;
}

BukuData* BukuRepository::getBukuData(int kode)
{
    QSqlQuery query;
    query.prepare("SELECT"
                  "   Buku.kd_buku,"
                  "   Buku.judul,"
                  "   Buku.penulis,"
                  "   Buku.jumlah_hilang,"
                  "   Buku.tahun_terbit,"
                  "   Kategori.kd_kategori,"
                  "   Kategori.nama_kategori,"
                  "   Penerbit.kd_penerbit,"
                  "   Penerbit.nama_penerbit "
                  "FROM Buku"
                  "   JOIN Kategori ON"
                  "       Buku.kd_kategori = Kategori.kd_kategori "
                  "   JOIN Penerbit ON"
                  "       Penerbit.kd_penerbit = Buku.kd_penerbit "
                  "WHERE Buku.kd_buku = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot get buku data " << query.lastError().text();

    if (query.next()) {
        return new BukuData(
            query.value("Buku.kd_buku").toInt(),
            query.value("Buku.judul").toString(),
            query.value("Buku.penulis").toString(),
            query.value("Buku.jumlah_hilang").toInt(),
            query.value("Buku.tahun_terbit").toInt(),
            query.value("Kategori.kd_kategori").toInt(),
            query.value("Kategori.nama_kategori").toString(),
            query.value("Penerbit.kd_penerbit").toInt(),
            query.value("Penerbit.nama_penerbit").toString()
            );
    } else {
        return new BukuData();
    }
}

void BukuRepository::addNew(QString judul, QString penulis, int tahunTerbit, int kodeKategori, int kodePenerbit)
{
    QSqlQuery query;
    if (!query.exec("SELECT MAX(CAST(kd_buku AS UNSIGNED)) FROM Buku"))
        qFatal() << "Error get max id " << query.lastError();

    int maxId = -1;
    if (query.next()) {
        maxId = query.value(0).toInt();
    }

    query.prepare("INSERT INTO Buku("
                  " kd_buku,"
                  " judul,"
                  " penulis,"
                  " tahun_terbit,"
                  " kd_kategori,"
                  " kd_penerbit"
                  ") VALUES ("
                  " :kode,"
                  " :judul,"
                  " :penulis,"
                  " :tahun_terbit,"
                  " :kategori,"
                  " :penerbit"
                  ")");

    query.bindValue(":kode", QString::number(maxId + 1).rightJustified(4, '0'));
    query.bindValue(":judul", judul);
    query.bindValue(":penulis", penulis);
    query.bindValue(":tahun_terbit", tahunTerbit);
    query.bindValue(":kategori", kodeKategori);
    query.bindValue(":penerbit", kodePenerbit);

    if (!query.exec())
        qFatal() << "Cannot add Buku " << query.lastError().text();

    emit dataChanged();
}

void BukuRepository::edit(int kode, QString judul, QString penulis, int jumlahHilang, int tahunTerbit, int kodeKategori, int kodePenerbit)
{
    QSqlQuery query;
    query.prepare("UPDATE Buku SET "
                  "judul = :judul,"
                  "penulis = :penulis,"
                  "jumlah_hilang = :jumlah,"
                  "tahun_terbit = :tahun_terbit,"
                  "kd_kategori = :kategori,"
                  "kd_penerbit = :penerbit "
                  "WHERE kd_buku = :kode");
    query.bindValue(":kode", kode);
    query.bindValue(":judul", judul);
    query.bindValue(":penulis", penulis);
    query.bindValue(":jumlah", jumlahHilang);
    query.bindValue(":tahun_terbit", tahunTerbit);
    query.bindValue(":kategori", kodeKategori);
    query.bindValue(":penerbit", kodePenerbit);

    if (!query.exec())
        qFatal() << "Cannot edit Buku " << query.lastError().text();

    emit dataChanged();
}

void BukuRepository::remove(int kode)
{
    QSqlQuery query;

    query.prepare("DELETE from Buku WHERE kd_buku = :kode");
    query.bindValue(":kode", kode);
    if (!query.exec())
        qFatal() << "Cannot remove Buku " << query.lastError().text();

    emit dataChanged();
}
