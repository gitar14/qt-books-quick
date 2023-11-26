#include "memberviewmodel.h"
#include "repositorymanager.h"

MemberViewModel::MemberViewModel(QObject *parent)
    : QObject{parent}, mRepository{RepositoryManager::getInstance()->getMember()}
{
    connect(mRepository, SIGNAL(dataChanged()), this, SLOT(refresh()));
    refresh();
}

QList<MemberData *> MemberViewModel::list() const
{
    return mList;
}

MemberData *MemberViewModel::selectedData() const
{
    return mSelectedData;
}

void MemberViewModel::refresh()
{
    mList = mRepository->getAll(mTextQuery);

    emit listChanged();
    refreshSelectedItem();
}

QString MemberViewModel::textQuery() const
{
    return mTextQuery;
}

void MemberViewModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    emit textQueryChanged();
    refresh();
}

void MemberViewModel::refreshSelectedItem()
{
    if (mSelectedIndex < 0 || mSelectedIndex >= mList.count())
        mSelectedData = new MemberData();
    else mSelectedData = mRepository->get(mList.at(mSelectedIndex)->kode());
    emit selectedDataChanged();
    emit hasSelectedItemChanged();
}

bool MemberViewModel::hasSelectedItem() const
{
    return mSelectedData->kode() != -1;
}

void MemberViewModel::setSelectedIndex(int index)
{
    mSelectedIndex = index;
    refreshSelectedItem();
}

void MemberViewModel::removeSelectedItem()
{
    mRepository->remove(mSelectedData->kode());
}
