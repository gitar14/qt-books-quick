#include "pengembalianviewmodel.h"
#include "repositorymanager.h"
#include "repository/settingrepository.h"
#include "usermanager.h"

PengembalianViewModel::PengembalianViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getPeminjaman()},
    mDenda{new PeminjamanDendaCalculator(this)}
{

}

void PengembalianViewModel::configure(int kode)
{
    mKode = kode;

    PeminjamanData* data = mRepository->get(mKode);
    mDenda->setTenggatPengembalian(data->tanggalPeminjaman().addDays(data->lamaPeminjaman()));
    delete data;

    QList<PeminjamanBukuData*> prevList = mBukuList;
    mBukuList = mRepository->getBukuList(mKode);
    mDenda->setBukuList(mBukuList);

    setTanggalPengembalian(QDate::currentDate());

    mDenda->setDendaTerlambatPerBuku(RepositoryManager::getInstance()->getSetting()->getDendaPerHari());

    emit bukuListChanged();

    qDeleteAll(prevList.begin(), prevList.end());
}

QDate PengembalianViewModel::tanggalPengembalian() const
{
    return mTanggalPengembalian;
}

void PengembalianViewModel::setTanggalPengembalian(const QDate &newTanggalPengembalian)
{
    if (mTanggalPengembalian == newTanggalPengembalian)
        return;
    mTanggalPengembalian = newTanggalPengembalian;
    mDenda->setTanggalPengembalian(mTanggalPengembalian);
    emit tanggalPengembalianChanged();
}

QList<PeminjamanBukuData *> PengembalianViewModel::bukuList() const
{
    return mBukuList;
}

PeminjamanDendaCalculator *PengembalianViewModel::denda() const
{
    return mDenda;
}

void PengembalianViewModel::submit()
{
    mRepository->tandaiDikembalikan(mKode, UserManager::getInstance()->loggedUser()->id(),
                                    tanggalPengembalian(), mDenda->dendaTerlambatPerBuku());
    mRepository->updateAllBuku(mKode, mBukuList);
}
