#include "penerbit.h"

PenerbitData::PenerbitData(int kode, const QString &nama, const QString &alamat)
    : QObject(),
    mKode(kode),
    mNama(nama),
    mAlamat(alamat)
{}

int PenerbitData::kode() const
{
    return mKode;
}

QString PenerbitData::nama() const
{
    return mNama;
}

QString PenerbitData::alamat() const
{
    return mAlamat;
}
