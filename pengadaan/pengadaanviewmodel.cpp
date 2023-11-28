#include "pengadaanviewmodel.h"
#include "repositorymanager.h"

PengadaanViewModel::PengadaanViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getPengadaan()},
    mSelectedData{new PengadaanDetailData()}
{
    refresh();
    connect(mRepository, SIGNAL(dataChanged()), this, SLOT(refresh()));
}

PengadaanViewModel::~PengadaanViewModel()
{
    qDeleteAll(mList.begin(), mList.end());
}

QList<PengadaanData*> PengadaanViewModel::list() const
{
    return mList;
}

QString PengadaanViewModel::textQuery() const
{
    return mTextQuery;
}

void PengadaanViewModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    emit textQueryChanged();
    refresh();
}

void PengadaanViewModel::setSelectedIndex(int newSelectedIndex)
{
    mSelectedIndex = newSelectedIndex;
    refreshSelectedItem();
}

PengadaanDetailData *PengadaanViewModel::selectedData() const
{
    return mSelectedData;
}

QList<PengadaanBukuData*> PengadaanViewModel::selectedBukuList() const
{
    return mSelectedBukuList;
}

void PengadaanViewModel::refresh()
{
    qDeleteAll(mList.begin(), mList.end());
    mList = RepositoryManager::getInstance()->getPengadaan()->getList(mTextQuery);

    emit listChanged();
    refreshSelectedItem();
}

void PengadaanViewModel::refreshSelectedItem()
{
    PengadaanDetailData* prevData = mSelectedData;
    if (mSelectedIndex < 0 || mSelectedIndex >= mList.count())
        mSelectedData = new PengadaanDetailData();
    else mSelectedData = mRepository->get(mList.at(mSelectedIndex)->kode());
    mSelectedData->setParent(this);

    mSelectedBukuList = mRepository->getBukuList(mSelectedData->kode());

    emit selectedDataChanged();
    emit hasSelectedItemChanged();
    emit selectedBukuListChanged();

    delete prevData;
}

bool PengadaanViewModel::hasSelectedItem() const
{
    return mSelectedData->kode() != -1;
}

void PengadaanViewModel::removeSelectedItem()
{
    int kode = mSelectedData->kode();
    mRepository->remove(kode);
    mRepository->removeAllBuku(kode);
}
