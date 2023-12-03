#include "penerbitviewmodel.h"
#include "repository/penerbitrepository.h"
#include "repositorymanager.h"

PenerbitViewModel::PenerbitViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getPenerbit()}
{
    refresh();
    connect(mRepository, SIGNAL(dataChanged()), this, SLOT(refresh()));
}


void PenerbitViewModel::refreshSelectedItem()
{
    if (mSelectedIndex < 0 || mSelectedIndex >= mList.count())
        mSelectedData.reset(new PenerbitDetailData());
    else mSelectedData.reset(mRepository->get(mList.at(mSelectedIndex)->kode()));

    emit selectedDataChanged();
    emit hasSelectedItemChanged();
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
    refresh();
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

PenerbitDetailData *PenerbitViewModel::selectedData() const
{
    return mSelectedData.get();
}

bool PenerbitViewModel::hasSelectedItem() const
{
    return mSelectedData->kode() != -1;
}

void PenerbitViewModel::refresh()
{
    mList = mRepository->getAll(mTextQuery);
    emit listChanged();

    refreshSelectedItem();
}
