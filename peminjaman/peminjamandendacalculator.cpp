#include "peminjamandendacalculator.h"

PeminjamanDendaCalculator::PeminjamanDendaCalculator(QObject *parent)
    : QObject{parent}
{
}

int PeminjamanDendaCalculator::dendaTerlambatPerBuku() const
{
    return mDendaTerlambatPerBuku;
}

void PeminjamanDendaCalculator::setDendaTerlambatPerBuku(int newDendaTenggatPerBuku)
{
    if (mDendaTerlambatPerBuku == newDendaTenggatPerBuku)
        return;
    mDendaTerlambatPerBuku = newDendaTenggatPerBuku;
    emit dendaTerlambatPerBukuChanged();
    calculateDenda();
}

QDate PeminjamanDendaCalculator::tenggatPengembalian() const
{
    return mTenggatPengembalian;
}

void PeminjamanDendaCalculator::setTenggatPengembalian(const QDate &newTenggatPengembalian)
{
    if (mTenggatPengembalian == newTenggatPengembalian)
        return;
    mTenggatPengembalian = newTenggatPengembalian;
    emit tenggatPengembalianChanged();
    calculateDenda();
}

QDate PeminjamanDendaCalculator::tanggalPengembalian() const
{
    return mTanggalPengembalian;
}

void PeminjamanDendaCalculator::setTanggalPengembalian(const QDate &newTanggalPengembalian)
{
    if (mTanggalPengembalian == newTanggalPengembalian)
        return;
    mTanggalPengembalian = newTanggalPengembalian;
    emit tanggalPengembalianChanged();
    calculateDenda();
}

int PeminjamanDendaCalculator::totalDendaTerlambat() const
{
    return mTotalDendaTerlambat;
}

void PeminjamanDendaCalculator::calculateDenda()
{
    const int jarakHari = mTenggatPengembalian.daysTo(mTanggalPengembalian);
    mTotalDendaTerlambat = (jarakHari < 0 ? 0 : jarakHari) * mDendaTerlambatPerBuku * mBukuList.length();
    emit totalDendaTerlambatChanged();

    int denda = mTotalDendaTerlambat;
    QListIterator<PeminjamanBukuData*> iterator(mBukuList);
    while (iterator.hasNext()) {
        denda += iterator.next()->denda();
    }
    mTotalDenda = denda;
    emit totalDendaChanged();
}

int PeminjamanDendaCalculator::totalDenda() const
{
    return mTotalDenda;
}

QList<PeminjamanBukuData *> PeminjamanDendaCalculator::bukuList() const
{
    return mBukuList;
}

void PeminjamanDendaCalculator::setBukuList(const QList<PeminjamanBukuData *> &newBukuList)
{
    if (mBukuList == newBukuList)
        return;
    for (int i = 0; i < mBukuList.length(); i++) {
        PeminjamanBukuData* data = mBukuList.at(i);
        disconnect(data, SIGNAL(dendaChanged()), this, SLOT(calculateDenda()));
    }
    mBukuList = newBukuList;
    for (int i = 0; i < mBukuList.length(); i++) {
        PeminjamanBukuData* data = mBukuList.at(i);
        connect(data, SIGNAL(dendaChanged()), this, SLOT(calculateDenda()));
    }
    emit bukuListChanged();
    emit calculateDenda();
}
