#include "bukuviewmodel.h"
#include "repositorymanager.h"

#include "repository/bukurepository.h"
#include "repository/pengadaanrepository.h"
#include "repository/peminjamanrepository.h"

BukuViewModel::BukuViewModel(QObject *parent)
    : BukuPilihViewModel{parent},
    mSelectedData{nullptr}
{
    connect(this, SIGNAL(selectedKodeChanged()), this, SLOT(refreshSelectedData()));
    refresh();
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

void BukuViewModel::removeSelected()
{
    mRepository->remove(selectedKode());
}

void BukuViewModel::refreshSelectedData()
{
    RepositoryManager* manager = RepositoryManager::getInstance();

    BukuData* prevData = mSelectedData;
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

    if (prevData != nullptr)
        delete prevData;
}
