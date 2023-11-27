#include "bukupilihviewmodel.h"
#include "repositorymanager.h"
#include "repository/kategorirepository.h"
#include "repository/penerbitrepository.h"

BukuPilihViewModel::BukuPilihViewModel(QObject *parent)
    : QObject{parent},
    mPenerbitFilterModel{new PenerbitFilterModel(this)}
{
    RepositoryManager* repositoryManager = RepositoryManager::getInstance();

    mKategoriFilterList = repositoryManager->getKategori()->getAll("");
    mKategoriFilterList.prepend(new KategoriData(-1, "Semua"));

    PenerbitModel* penerbitModel = repositoryManager->getPenerbit()->createListModel();
    penerbitModel->setParent(this);
    mPenerbitFilterModel->setSourceModel(penerbitModel);

    mRepository = repositoryManager->getBuku(),
    connect(mRepository, SIGNAL(dataChanged()), this, SLOT(refresh()));
    refresh();
}

QList<BukuData *> BukuPilihViewModel::list() const
{
    return mList;
}

PenerbitFilterModel *BukuPilihViewModel::penerbitFilterModel() const
{
    return mPenerbitFilterModel;
}

QList<int> BukuPilihViewModel::ignoredKode() const
{
    return mIgnoredKode;
}

void BukuPilihViewModel::setIgnoredKode(const QList<int> &newIgnoredKode)
{
    if (mIgnoredKode == newIgnoredKode)
        return;
    mIgnoredKode = newIgnoredKode;
    emit ignoredKodeChanged();
    refresh();
}

void BukuPilihViewModel::setSelectedIndex(int index)
{
    mSelectedIndex = index;
    refreshSelectedItem();
}

void BukuPilihViewModel::refresh()
{
    mList = mRepository->getList(mIgnoredKode, mTextQuery, mKategoriFilter, mPenerbitFilter);
    refreshSelectedItem();

    emit listChanged();
}

void BukuPilihViewModel::refreshSelectedItem()
{
    if (mSelectedIndex < 0 || mSelectedIndex >= mList.length())
        mSelectedKode = -1;
    else mSelectedKode = mList.at(mSelectedIndex)->kode();
    emit selectedKodeChanged();
    emit hasSelectedItemChanged();
}

QList<KategoriData *> BukuPilihViewModel::kategoriFilterList() const
{
    return mKategoriFilterList;
}

bool BukuPilihViewModel::hasSelectedItem() const
{
    return mSelectedKode != -1;
}

int BukuPilihViewModel::selectedKode() const
{
    return mSelectedKode;
}

QString BukuPilihViewModel::textQuery() const
{
    return mTextQuery;
}

void BukuPilihViewModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    emit textQueryChanged();
    refresh();
}

int BukuPilihViewModel::kategoriFilter() const
{
    return mKategoriFilter;
}

void BukuPilihViewModel::setKategoriFilter(int newKategoriFilter)
{
    if (mKategoriFilter == newKategoriFilter)
        return;
    mKategoriFilter = newKategoriFilter;
    emit kategoriFilterChanged();
    refresh();
}

int BukuPilihViewModel::penerbitFilter() const
{
    return mPenerbitFilter;
}

void BukuPilihViewModel::setPenerbitFilter(int newPenerbitFilter)
{
    if (mPenerbitFilter == newPenerbitFilter)
        return;
    mPenerbitFilter = newPenerbitFilter;
    emit penerbitFilterChanged();
    refresh();
}
