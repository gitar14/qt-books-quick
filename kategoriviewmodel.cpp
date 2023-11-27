#include "kategoriviewmodel.h"
#include "repository/kategorirepository.h"
#include "repositorymanager.h"

KategoriViewModel::KategoriViewModel(QObject *parent)
    : QObject{parent}, mRepository{RepositoryManager::getInstance()->getKategori()}
{
    refresh();
    connect(mRepository, SIGNAL(dataChanged()), this, SLOT(refresh()));
}


void KategoriViewModel::setSelectedIndex(int index)
{
    mSelectedIndex = index;
    refreshSelectedItem();
}


QString KategoriViewModel::textQuery() const
{
    return mTextQuery;
}

void KategoriViewModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    emit textQueryChanged();
    refresh();
}

void KategoriViewModel::removeSelected()
{
    mRepository->remove(mSelectedData->kode());
}

void KategoriViewModel::refreshSelectedItem()
{
    if (mSelectedIndex < 0 || mSelectedIndex >= mList.length())
        mSelectedData = new KategoriData();
    else mSelectedData = mRepository->get(mList.at(mSelectedIndex)->kode());

    emit selectedDataChanged();
    emit hasSelectedItemChanged();
}

QList<KategoriData *> KategoriViewModel::list() const
{
    return mList;
}

bool KategoriViewModel::hasSelectedItem() const
{
    return mSelectedData->kode() != -1;
}

KategoriData *KategoriViewModel::selectedData() const
{
    return mSelectedData;
}

void KategoriViewModel::refresh()
{
    mList = mRepository->getAll(mTextQuery);

    emit listChanged();
    refreshSelectedItem();
}
