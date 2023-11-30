#include "buku.h"


BukuData::BukuData(int kode,
                   QString judul,
                   QString penulis,
                   int kodeKategori,
                   QString namaKategori): QObject(),
    mKode{kode},
    mJudul{judul},
    mPenulis{penulis},
    mKodeKategori{kodeKategori},
    mNamaKategori{namaKategori} {

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

int BukuData::kodeKategori() const
{
    return mKodeKategori;
}

QString BukuData::namaKategori() const
{
    return mNamaKategori;
}

BukuDetailData::BukuDetailData(
    int kode,
    QString judul,
    QString penulis,
    int jumlahHilang,
    int tahunTerbit,
    int kodeKategori,
    QString namaKategori,
    int kodePenerbit,
    QString namaPenerbit
    ) : BukuData(kode, judul, penulis, kodeKategori, namaKategori),
    mJumlahHilang{jumlahHilang},
    mTahunTerbit{tahunTerbit},
    mKodePenerbit{kodePenerbit},
    mNamaPenerbit{namaPenerbit}
{

}

int BukuDetailData::kodePenebit() const
{
    return mKodePenerbit;
}

QString BukuDetailData::namaPenerbit() const
{
    return mNamaPenerbit;
}

int BukuDetailData::jumlahHilang() const
{
    return mJumlahHilang;
}

int BukuDetailData::tahunTerbit() const
{
    return mTahunTerbit;
}
