#include "kategoriviewmodel.h"
#include "repository/kategorirepository.h"
#include "repositorymanager.h"

KategoriViewModel::KategoriViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getKategori()},
    mSelectedData{nullptr}
{
    refresh();
    connect(mRepository, SIGNAL(dataChanged()), this, SLOT(refresh()));
}

KategoriViewModel::~KategoriViewModel()
{
    qDeleteAll(mList);
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
    KategoriData* prevData = mSelectedData;
    if (mSelectedIndex < 0 || mSelectedIndex >= mList.length())
        mSelectedData = new KategoriData();
    else mSelectedData = mRepository->get(mList.at(mSelectedIndex)->kode());
    mSelectedData->setParent(this);

    emit selectedDataChanged();
    emit hasSelectedItemChanged();

    if (prevData != nullptr)
        delete prevData;
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
    QList<KategoriData*> prevList = mList;
    mList = mRepository->getAll(mTextQuery);

    emit listChanged();
    refreshSelectedItem();

    qDeleteAll(prevList);
}
