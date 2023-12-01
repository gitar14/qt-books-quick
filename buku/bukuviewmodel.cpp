#include "bukuviewmodel.h"
#include "repositorymanager.h"

#include "repository/bukurepository.h"
#include "repository/pengadaanrepository.h"
#include "repository/peminjamanrepository.h"

BukuJumlahViewData::BukuJumlahViewData(int jumlahPengadaan, int jumlahHilang, int jumlahDipinjam)
    : QObject(),
    mPengadaan{jumlahPengadaan},
    mTidakHilang{jumlahPengadaan - jumlahHilang},
    mDipinjam{jumlahDipinjam},
    mTersedia{mTidakHilang - jumlahDipinjam}
{

}

int BukuJumlahViewData::pengadaan() const
{
    return mPengadaan;
}

int BukuJumlahViewData::tidakHilang() const
{
    return mTidakHilang;
}

int BukuJumlahViewData::dipinjam() const
{
    return mDipinjam;
}

int BukuJumlahViewData::tersedia() const
{
    return mTersedia;
}

BukuViewModel::BukuViewModel(QObject *parent)
    : BukuPilihViewModel{parent},
    mSelectedData{new BukuDetailData()},
    mSelectedDataJumlah{new BukuJumlahViewData()}
{
    connect(this, SIGNAL(selectedKodeChanged()), this, SLOT(refreshSelectedData()));
    init();
}

BukuDetailData *BukuViewModel::selectedData() const
{
    return mSelectedData.get();
}

void BukuViewModel::removeSelected()
{
    mRepository->remove(selectedKode());
}

void BukuViewModel::refreshSelectedData()
{
    RepositoryManager* manager = RepositoryManager::getInstance();

    if (selectedKode() != -1) {
        mSelectedData.reset(mRepository->getBukuData(selectedKode()));
        mSelectedDataJumlah.reset(new BukuJumlahViewData(
            manager->getPengadaan()->getJumlahPengadaanBuku(selectedKode()),
            mSelectedData->jumlahHilang(),
            manager->getPeminjaman()->getJumlahBukuDipinjam(selectedKode())
            ));
    } else {
        mSelectedData.reset(new BukuDetailData());
        mSelectedDataJumlah.reset(new BukuJumlahViewData());
    }
    mSelectedData->setParent(this);

    emit selectedDataChanged();
    emit selectedDataJumlahChanged();
}

BukuJumlahViewData* BukuViewModel::selectedDataJumlah() const
{
    return mSelectedDataJumlah.get();
}
