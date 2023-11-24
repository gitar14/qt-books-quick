#include "bukuviewmodel.h"
#include "repositorymanager.h"
#include "repository/kategorirepository.h"
#include "repository/penerbitrepository.h"
#include "repository/bukurepository.h"
#include "repository/pengadaanrepository.h"
#include "repository/peminjamanrepository.h"
#include "repository/list/kategorimodel.h"
#include "repository/list/penerbitmodel.h"

BukuViewModel::BukuViewModel(QObject *parent)
    : QObject{parent},
    mKategoriFilterModel{new KategoriFilterModel(this)},
    mPenerbitFilterModel{new PenerbitFilterModel(this)},
    mSelectedData{new BukuData()}
{
    RepositoryManager* repositoryManager = RepositoryManager::getInstance();

    KategoriModel* kategoriModel = repositoryManager->getKategori()->createListModel();
    kategoriModel->setParent(this);
    mKategoriFilterModel->setSourceModel(kategoriModel);

    PenerbitModel* penerbitModel = repositoryManager->getPenerbit()->createListModel();
    penerbitModel->setParent(this);
    mPenerbitFilterModel->setSourceModel(penerbitModel);

    BukuRepository* bukuRepository = repositoryManager->getBuku();
    mListModel = bukuRepository->createListModel();
    mListModel->setParent(this);
    connect(bukuRepository, SIGNAL(dataChanged()), this, SLOT(refreshSelectedItem()));
}

BukuListModel *BukuViewModel::listModel() const
{
    return mListModel;
}

KategoriFilterModel *BukuViewModel::kategoriFilterModel() const
{
    return mKategoriFilterModel;
}

PenerbitFilterModel *BukuViewModel::penerbitFilterModel() const
{
    return mPenerbitFilterModel;
}

void BukuViewModel::setSelectedIndex(int index)
{
    mSelectedIndex = index;
    refreshSelectedItem();
}

BukuData *BukuViewModel::selectedData() const
{
    return mSelectedData;
}

bool BukuViewModel::hasSelectedItem() const
{
    return mSelectedData->kode() != -1;
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
    QVariant kodeVar = mListModel->data(mListModel->index(mSelectedIndex, 0), BukuListModel::KodeRole);
    RepositoryManager* manager = RepositoryManager::getInstance();
    mSelectedData->deleteLater();
    if (!kodeVar.isNull()) {
        int kode = kodeVar.toInt();
        mSelectedData = manager->getBuku()->getBukuData(kode);
        mSelectedJumlahPengadaan = manager->getPengadaan()->getJumlahPengadaanBuku(kode);
        mSelectedJumlahDipinjam = manager->getPeminjaman()->getJumlahBukuDipinjam(kode);
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

QString BukuViewModel::textQuery() const
{
    return mTextQuery;
}

void BukuViewModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    mListModel->setTextQuery(mTextQuery);
    emit textQueryChanged();
}

int BukuViewModel::kategoriFilter() const
{
    return mKategoriFilter;
}

void BukuViewModel::setKategoriFilter(int newKategoriFilter)
{
    if (mKategoriFilter == newKategoriFilter)
        return;
    mKategoriFilter = newKategoriFilter;
    mListModel->setKategoriFilter(mKategoriFilter);
    emit kategoriFilter();
}

int BukuViewModel::penerbitFilter() const
{
    return mPenerbitFilter;
}

void BukuViewModel::setPenerbitFilter(int newPenerbitFilter)
{
    if (mPenerbitFilter == newPenerbitFilter)
        return;
    mPenerbitFilter = newPenerbitFilter;
    mListModel->setPenerbitFilter(mPenerbitFilter);
    emit penerbitFilter();
}
