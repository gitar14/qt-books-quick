#include "pengadaan.h"

PengadaanData::PengadaanData(int kode, QString sumber, QDate tanggalPengadaan)
    : QObject(), mKode{kode}, mSumber{sumber}, mTanggalPengadaan{tanggalPengadaan}
{

}

int PengadaanData::kode() const
{
    return mKode;
}

QString PengadaanData::sumber() const
{
    return mSumber;
}

QDate PengadaanData::tanggalPengadaan() const
{
    return mTanggalPengadaan;
}

PengadaanDetailData::PengadaanDetailData(
    int kode,
    const QString &sumber,
    const QDate &tanggalPengadaan,
    QString userId,
    const QString &userNamaDepan,
    const QString &userNamaBelakang)
    : PengadaanData(kode, sumber, tanggalPengadaan),
    mUserId(userId),
    mUserNamaDepan(userNamaDepan),
    mUserNamaBelakang(userNamaBelakang)
{}


QString PengadaanDetailData::userId() const
{
    return mUserId;
}

QString PengadaanDetailData::userNamaDepan() const
{
    return mUserNamaDepan;
}

QString PengadaanDetailData::userNamaBelakang() const
{
    return mUserNamaBelakang;
}

QString PengadaanDetailData::userNama() const
{
    return mUserNamaDepan + " " + mUserNamaBelakang;
}

PengadaanBukuData::PengadaanBukuData(int kodeBuku, int jumlah, QString judul)
    : QObject(), mKodeBuku{kodeBuku}, mJumlah{jumlah}, mJudul{judul}
{

}

int PengadaanBukuData::kodeBuku() const
{
    return mKodeBuku;
}

int PengadaanBukuData::jumlah() const
{
    return mJumlah;
}

QString PengadaanBukuData::judul() const
{
    return mJudul;
}

void PengadaanBukuData::setJumlah(int newJumlah)
{
    if (mJumlah == newJumlah)
        return;
    mJumlah = newJumlah;
    emit jumlahChanged();
}
