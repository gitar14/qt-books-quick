#include "peminjamaneditviewmodel.h"
#include "repository/bukurepository.h"
#include "repositorymanager.h"
#include "repository/memberrepository.h"
#include "repository/userrepository.h"
#include "usermanager.h"

PeminjamanEditViewModel::PeminjamanEditViewModel(QObject *parent)
    : QObject{parent}, mRepository{RepositoryManager::getInstance()->getPeminjaman()}
{

}

void PeminjamanEditViewModel::configure(int kode)
{
    mKode = kode;
    QScopedPointer<PeminjamanData> data(kode != -1 ? mRepository->get(kode) : new PeminjamanData());
    mKodeMember = data->kodeMember();
    mNamaMember = data->namaMember();
    mTanggalPeminjaman = data->tanggalPeminjaman();
    if (!mTanggalPeminjaman.isValid()) mTanggalPeminjaman = QDate::currentDate();
    mLamaPeminjaman = data->lamaPeminjaman();

    mBukuList = mRepository->getBukuList(kode);

    emit kodeMemberChanged();
    emit namaMemberChanged();
    emit tanggalPeminjamanChanged();
    emit lamaPeminjamanChanged();
    emit bukuListChanged();

    refreshAvailableBuku();
}

int PeminjamanEditViewModel::kodeMember() const
{
    return mKodeMember;
}

void PeminjamanEditViewModel::setKodeMember(int newKodeMember)
{
    if (mKodeMember == newKodeMember)
        return;
    mKodeMember = newKodeMember;
    emit kodeMemberChanged();

    QScopedPointer<MemberData> data(RepositoryManager::getInstance()->getMember()->get(mKodeMember));
    mNamaMember = data->nama();

    emit namaMemberChanged();
}

QString PeminjamanEditViewModel::namaMember() const
{
    return mNamaMember;
}

QDate PeminjamanEditViewModel::tanggalPeminjaman() const
{
    return mTanggalPeminjaman;
}

void PeminjamanEditViewModel::setTanggalPeminjaman(const QDate &newTanggalPeminjaman)
{
    if (mTanggalPeminjaman == newTanggalPeminjaman)
        return;
    mTanggalPeminjaman = newTanggalPeminjaman;
    emit tanggalPeminjamanChanged();
}

int PeminjamanEditViewModel::lamaPeminjaman() const
{
    return mLamaPeminjaman;
}

void PeminjamanEditViewModel::setLamaPeminjaman(int newLamaPeminjaman)
{
    if (mLamaPeminjaman == newLamaPeminjaman)
        return;
    mLamaPeminjaman = newLamaPeminjaman;
    emit lamaPeminjamanChanged();
}

QList<PeminjamanBukuData *> PeminjamanEditViewModel::bukuList() const
{
    return mBukuList;
}

void PeminjamanEditViewModel::appendBuku(int kodeBuku)
{
    QScopedPointer<BukuData> buku(RepositoryManager::getInstance()->getBuku()->getBukuData(kodeBuku));
    mBukuList.append(new PeminjamanBukuData(buku->kode(), buku->judul(), 0));
    emit bukuListChanged();

    refreshAvailableBuku();
}

void PeminjamanEditViewModel::removeBuku(int index)
{
    mBukuList.remove(index);
    emit bukuListChanged();

    refreshAvailableBuku();
}

QList<int> PeminjamanEditViewModel::kodeBukuList() const
{
    return mKodeBukuList;
}

int PeminjamanEditViewModel::isBukuAvailable() const
{
    return mIsBukuAvailable;
}

void PeminjamanEditViewModel::submit()
{
    int kode = mKode;
    if (kode == -1) {
        kode = mRepository->add(mKodeMember, UserManager::getInstance()->loggedUser()->id(),
                                mTanggalPeminjaman, mLamaPeminjaman);
        mRepository->addAllBuku(kode, mBukuList);
    } else {
        mRepository->update(kode, mKodeMember, mTanggalPeminjaman, mLamaPeminjaman);
        mRepository->updateAllBuku(kode, mBukuList);
    }
}

void PeminjamanEditViewModel::refreshAvailableBuku()
{
    mKodeBukuList.clear();
    for (int i = 0; i <  mBukuList.count(); i++) {
        mKodeBukuList.append(mBukuList.at(i)->kodeBuku());
    }

    emit kodeBukuListChanged();

    mIsBukuAvailable = RepositoryManager::getInstance()->getBuku()->isBookAvailable(mKodeBukuList);
    emit isBukuAvailableChanged();
}

bool PeminjamanEditViewModel::isNew() const
{
    return mKode == -1;
}
