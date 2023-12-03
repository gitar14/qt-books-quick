#include "penerbit.h"

PenerbitData::PenerbitData(int kode, const QString &nama)
    : QObject(),
    mKode(kode),
    mNama(nama)
{}

int PenerbitData::kode() const
{
    return mKode;
}

QString PenerbitData::nama() const
{
    return mNama;
}

PenerbitDetailData::PenerbitDetailData(int kode, const QString &nama, const QString &alamat)
    : PenerbitData(kode, nama),
    mAlamat(alamat)
{

}

QString PenerbitDetailData::alamat() const
{
    return mAlamat;
}
