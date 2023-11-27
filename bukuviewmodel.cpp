#include "bukuviewmodel.h"
#include "repositorymanager.h"

#include "repository/bukurepository.h"
#include "repository/pengadaanrepository.h"
#include "repository/peminjamanrepository.h"

BukuViewModel::BukuViewModel(QObject *parent)
    : BukuPilihViewModel{parent},
    mSelectedData{new BukuData()}
{
}

BukuData *BukuViewModel::selectedData() const
{
    return mSelectedData;
}

int BukuViewModel::selectedJumlahPengadaan() const
{
    return mSelectedJumlahPengadaan;
}

int BukuViewModel::selectedJumlahDipinjam() const
{
    return mSelectedJumlahDipinjam;
}

void BukuViewModel::refreshSelectedItem()
{
    BukuPilihViewModel::refreshSelectedItem();
    mSelectedData->deleteLater();

    RepositoryManager* manager = RepositoryManager::getInstance();

    if (selectedKode() != -1) {
        mSelectedData = mRepository->getBukuData(selectedKode());
        mSelectedJumlahPengadaan = manager->getPengadaan()->getJumlahPengadaanBuku(selectedKode());
        mSelectedJumlahDipinjam = manager->getPeminjaman()->getJumlahBukuDipinjam(selectedKode());
    } else {
        mSelectedData = new BukuData();
        mSelectedJumlahPengadaan = 0;
        mSelectedJumlahDipinjam = 0;
    }
    mSelectedData->setParent(this);

    emit selectedDataChanged();
    emit selectedJumlahPengadaanChanged();
    emit selectedJumlahDipinjamChanged();
}
