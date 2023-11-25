#include "bukupilihviewmodel.h"
#include "repositorymanager.h"

BukuPilihViewModel::BukuPilihViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getBuku()}
{
    connect(mRepository, SIGNAL(dataChanged()), this, SLOT(refresh()));
    refresh();
}

QList<BukuData *> BukuPilihViewModel::list() const
{
    return mList;
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
    mList = mRepository->getList(mIgnoredKode, "", -1, -1);
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

bool BukuPilihViewModel::hasSelectedItem() const
{
    return mSelectedKode != -1;
}

int BukuPilihViewModel::selectedKode() const
{
    return mSelectedKode;
}
