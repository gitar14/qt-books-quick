#include "peminjaman.h"

PeminjamanData::PeminjamanData(
    int kode,
    int kodeMember,
    QString namaDepanMember,
    QString namaBelakangMember,
    QDate tanggalPeminjaman,
    int lamaPeminjaman,
    QDate tanggalPengembalian,
    int dendaTerlambatPerBuku
    ): QObject(),
    mKode{kode},
    mKodeMember{kodeMember},
    mNamaDepanMember{namaDepanMember},
    mNamaBelakangMember{namaBelakangMember},
    mTanggalPeminjaman{tanggalPeminjaman},
    mLamaPeminjaman{lamaPeminjaman},
    mTanggalPengembalian{tanggalPengembalian},
    mDendaTerlambatPerBuku{dendaTerlambatPerBuku}
{

}


int PeminjamanData::kode() const
{
    return mKode;
}

int PeminjamanData::kodeMember() const
{
    return mKodeMember;
}

QString PeminjamanData::namaDepanMember() const
{
    return mNamaDepanMember;
}

QString PeminjamanData::namaBelakangMember() const
{
    return mNamaBelakangMember;
}

QDate PeminjamanData::tanggalPeminjaman() const
{
    return mTanggalPeminjaman;
}

int PeminjamanData::lamaPeminjaman() const
{
    return mLamaPeminjaman;
}

QDate PeminjamanData::tanggalPengembalian() const
{
    return mTanggalPengembalian;
}

int PeminjamanData::dendaTerlambatPerBuku() const
{
    return mDendaTerlambatPerBuku;
}

QString PeminjamanData::namaMember() const
{
    return mNamaDepanMember + " " + mNamaBelakangMember;
}

QDate PeminjamanData::tenggatPengembalian() const
{
    return mTanggalPeminjaman.addDays(mLamaPeminjaman);
}

bool PeminjamanData::sudahDikembalikan() const
{
    return mTanggalPengembalian.isValid();
}

PeminjamanBukuData::PeminjamanBukuData(int kodeBuku, QString judul, int denda)
    : QObject(), mKodeBuku{kodeBuku}, mJudul{judul}, mDenda{denda}
{

}

int PeminjamanBukuData::kodeBuku() const
{
    return mKodeBuku;
}

QString PeminjamanBukuData::judul() const
{
    return mJudul;
}

int PeminjamanBukuData::denda() const
{
    return mDenda;
}

void PeminjamanBukuData::setDenda(int newDenda)
{
    if (mDenda == newDenda)
        return;
    mDenda = newDenda;
    emit dendaChanged();
}

PeminjamanDetailData::PeminjamanDetailData(int kode,
                                           int kodeMember,
                                           const QString &namaDepanMember,
                                           const QString &namaBelakangMember,
                                           const QDate &tanggalPeminjaman,
                                           int lamaPeminjaman,
                                           const QDate &tanggalPengembalian,
                                           int dendaTerlambatPerBuku,
                                           const QString &peminjamanUserId,
                                           const QString &peminjamanUserNamaDepan,
                                           const QString &peminjamanUserNamaBelakang,
                                           const QString &pengembalianUserId,
                                           const QString &pengembalianUserNamaDepan,
                                           const QString &pengembalianUserNamaBelakang)
    : PeminjamanData(kode, kodeMember, namaDepanMember, namaBelakangMember, tanggalPeminjaman, lamaPeminjaman, tanggalPengembalian, dendaTerlambatPerBuku),
    mPeminjamanUserId(peminjamanUserId),
    mPeminjamanUserNamaDepan(peminjamanUserNamaDepan),
    mPeminjamanUserNamaBelakang(peminjamanUserNamaBelakang),
    mPengembalianUserId(pengembalianUserId),
    mPengembalianUserNamaDepan(pengembalianUserNamaDepan),
    mPengembalianUserNamaBelakang(pengembalianUserNamaBelakang)
{}

QString PeminjamanDetailData::peminjamanUserId() const
{
    return mPeminjamanUserId;
}

QString PeminjamanDetailData::peminjamanUserNamaDepan() const
{
    return mPeminjamanUserNamaDepan;
}

QString PeminjamanDetailData::peminjamanUserNamaBelakang() const
{
    return mPeminjamanUserNamaBelakang;
}

QString PeminjamanDetailData::pengembalianUserId() const
{
    return mPengembalianUserId;
}

QString PeminjamanDetailData::pengembalianUserNamaDepan() const
{
    return mPengembalianUserNamaDepan;
}

QString PeminjamanDetailData::pengembalianUserNamaBelakang() const
{
    return mPengembalianUserNamaBelakang;
}

QString PeminjamanDetailData::peminjamanUserNama() const
{
    return mPeminjamanUserNamaDepan + " " + mPeminjamanUserNamaBelakang;
}

QString PeminjamanDetailData::pengembalianUserNama() const
{
    return mPengembalianUserNamaDepan + " " + mPengembalianUserNamaBelakang;
}
