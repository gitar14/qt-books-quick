#include "buku.h"


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
