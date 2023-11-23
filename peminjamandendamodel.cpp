#include "peminjamandendamodel.h"
#include "sqlhelper.h"

PeminjamanDendaModel::PeminjamanDendaModel(QObject *parent)
    : QObject{parent}, mDendaTerlambatPerBuku{SQLHelper::getDendaPerHari()}
{
}

QList<int> PeminjamanDendaModel::dendaTambahanBukuList() const
{
    return mDendaTambahanBukuList;
}

void PeminjamanDendaModel::setDendaTambahanBukuList(const QList<int> &newDendaTambahanBukuList)
{
    if (mDendaTambahanBukuList == newDendaTambahanBukuList)
        return;
    mDendaTambahanBukuList = newDendaTambahanBukuList;
    emit dendaTambahanBukuListChanged();
    calculateDenda();
}

int PeminjamanDendaModel::dendaTerlambatPerBuku() const
{
    return mDendaTerlambatPerBuku;
}

void PeminjamanDendaModel::setDendaTerlambatPerBuku(int newDendaTenggatPerBuku)
{
    if (mDendaTerlambatPerBuku == newDendaTenggatPerBuku)
        return;
    mDendaTerlambatPerBuku = newDendaTenggatPerBuku;
    emit dendaTerlambatPerBukuChanged();
    calculateDenda();
}

QDate PeminjamanDendaModel::tenggatPengembalian() const
{
    return mTenggatPengembalian;
}

void PeminjamanDendaModel::setTenggatPengembalian(const QDate &newTenggatPengembalian)
{
    if (mTenggatPengembalian == newTenggatPengembalian)
        return;
    mTenggatPengembalian = newTenggatPengembalian;
    emit tenggatPengembalianChanged();
    calculateDenda();
}

QDate PeminjamanDendaModel::tanggalPengembalian() const
{
    return mTanggalPengembalian;
}

void PeminjamanDendaModel::setTanggalPengembalian(const QDate &newTanggalPengembalian)
{
    if (mTanggalPengembalian == newTanggalPengembalian)
        return;
    mTanggalPengembalian = newTanggalPengembalian;
    emit tanggalPengembalianChanged();
    calculateDenda();
}

int PeminjamanDendaModel::totalDendaTerlambat() const
{
    return mTotalDendaTerlambat;
}

void PeminjamanDendaModel::calculateDenda()
{
    const int jarakHari = mTenggatPengembalian.daysTo(mTanggalPengembalian);
    mTotalDendaTerlambat = (jarakHari < 0 ? 0 : jarakHari) * mDendaTerlambatPerBuku * mDendaTambahanBukuList.length();
    emit totalDendaTerlambatChanged();

    int denda = mTotalDendaTerlambat;
    QListIterator<int> iterator(mDendaTambahanBukuList);
    while (iterator.hasNext()) {
        denda += iterator.next();
    }
    mTotalDenda = denda;
    emit totalDendaChanged();
}

int PeminjamanDendaModel::totalDenda() const
{
    return mTotalDenda;
}
