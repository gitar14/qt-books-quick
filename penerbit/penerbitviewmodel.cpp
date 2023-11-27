#include "penerbitviewmodel.h"
#include "repository/penerbitrepository.h"
#include "repositorymanager.h"

PenerbitViewModel::PenerbitViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getPenerbit()},
    mSelectedData{nullptr}
{
    refresh();
    connect(mRepository, SIGNAL(dataChanged()), this, SLOT(refresh()));
}


void PenerbitViewModel::refreshSelectedItem()
{
    PenerbitData* prevData = mSelectedData;
    if (mSelectedIndex < 0 || mSelectedIndex >= mList.count())
        mSelectedData = new PenerbitData();
    else mSelectedData = mRepository->get(mList.at(mSelectedIndex)->kode());

    emit selectedDataChanged();
    emit hasSelectedItemChanged();

    if (prevData != nullptr)
        delete prevData;
}

QString PenerbitViewModel::textQuery() const
{
    return mTextQuery;
}

void PenerbitViewModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    emit textQueryChanged();
}

void PenerbitViewModel::setSelectedIndex(int index)
{
    mSelectedIndex = index;
    refreshSelectedItem();
}

void PenerbitViewModel::removeSelected()
{
    RepositoryManager::getInstance()->getPenerbit()->remove(mSelectedData->kode());
}

QList<PenerbitData *> PenerbitViewModel::list() const
{
    return mList;
}

PenerbitData *PenerbitViewModel::selectedData() const
{
    return mSelectedData;
}

bool PenerbitViewModel::hasSelectedItem() const
{
    return mSelectedData->kode() != -1;
}

void PenerbitViewModel::refresh()
{
    QList<PenerbitData*> prevList = mList;
    mList = mRepository->getAll(mTextQuery);
    emit listChanged();

    refreshSelectedItem();

    qDeleteAll(prevList);
}
