#include "member.h"

MemberData::MemberData(int kode,
    const QString &namaDepan,
    const QString &namaBelakang)
    : QObject(),
    mKode(kode),
    mNamaDepan(namaDepan),
    mNamaBelakang(namaBelakang)
{}


int MemberData::kode() const
{
    return mKode;
}

QString MemberData::namaDepan() const
{
    return mNamaDepan;
}

QString MemberData::namaBelakang() const
{
    return mNamaBelakang;
}

QString MemberData::nama() const
{
    return mNamaDepan + " " + mNamaBelakang;
}


MemberDetailData::MemberDetailData(int kode,
                                   const QString &namaDepan,
                                   const QString &namaBelakang,
                                   const QDate &tanggalLahir)
    : MemberData(kode, namaDepan, namaBelakang),
    mTanggalLahir(tanggalLahir)
{

}

QDate MemberDetailData::tanggalLahir() const
{
    return mTanggalLahir;
}

int MemberDetailData::umur() const
{
    QDate now = QDate::currentDate();
    int age = now.year() - mTanggalLahir.year();
    if (now.month() < mTanggalLahir.month())
        age--;
    else if (now.month() == mTanggalLahir.month() && now.day() < mTanggalLahir.day())
        age--;

    return age;
}
