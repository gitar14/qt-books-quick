#include "member.h"

MemberData::MemberData(
    int kode,
    const QString &namaDepan,
    const QString &namaBelakang,
    const QDate &tanggalLahir
    )
    : QObject(),
    mKode(kode),
    mNamaDepan(namaDepan),
    mNamaBelakang(namaBelakang),
    mTanggalLahir(tanggalLahir)
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

QDate MemberData::tanggalLahir() const
{
    return mTanggalLahir;
}

QString MemberData::nama() const
{
    return mNamaDepan + " " + mNamaBelakang;
}

int MemberData::umur() const
{
    QDate now = QDate::currentDate();
    int age = now.year() - mTanggalLahir.year();
    if (now.month() < mTanggalLahir.month())
        age--;
    else if (now.month() == mTanggalLahir.month() && now.day() < mTanggalLahir.day())
        age--;

    return age;
}
