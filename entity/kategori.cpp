#include "kategori.h"

KategoriData::KategoriData(int kode, const QString &nama) :
    QObject(),
    mKode(kode),
    mNama(nama)
{}


int KategoriData::kode() const
{
    return mKode;
}

QString KategoriData::nama() const
{
    return mNama;
}
