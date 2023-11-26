#include "peminjamaneditviewmodel.h"
#include "repository/bukurepository.h"
#include "repositorymanager.h"
#include "repository/memberrepository.h"

PeminjamanEditViewModel::PeminjamanEditViewModel(QObject *parent)
    : QObject{parent}, mRepository{RepositoryManager::getInstance()->getPeminjaman()}
{

}

void PeminjamanEditViewModel::configure(int kode)
{
    mKode = kode;
    PeminjamanData* data = mRepository->get(kode);
    mKodeMember = data->kodeMember();
    mNamaMember = data->namaDepanMember() + " " + data->namaBelakangMember();
    mTanggalPeminjaman = data->tanggalPeminjaman();
    if (!mTanggalPeminjaman.isValid()) mTanggalPeminjaman = QDate::currentDate();
    mLamaPeminjaman = data->lamaPeminjaman();
    delete data;

    qDeleteAll(mBukuList.begin(), mBukuList.end());
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

    MemberData* data = RepositoryManager::getInstance()->getMember()->get(mKodeMember);
    mNamaMember = data->namaDepan() + " " + data->namaBelakang();
    delete data;

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
    BukuData* buku = RepositoryManager::getInstance()->getBuku()->getBukuData(kodeBuku);
    mBukuList.append(new PeminjamanBukuData(buku->kode(), buku->judul(), 0));
    delete buku;
    emit bukuListChanged();

    refreshAvailableBuku();
}

void PeminjamanEditViewModel::removeBuku(int index)
{
    delete mBukuList[index];
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
        kode = mRepository->add(mKodeMember, mTanggalPeminjaman, mLamaPeminjaman);
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
