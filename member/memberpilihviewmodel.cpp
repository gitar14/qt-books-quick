#include "memberpilihviewmodel.h"
#include "repositorymanager.h"

MemberPilihViewModel::MemberPilihViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getMember()}
{
    connect(mRepository, SIGNAL(dataChanged()), this, SLOT(refresh()));
}

QList<MemberData *> MemberPilihViewModel::list() const
{
    return mList;
}

int MemberPilihViewModel::selectedKode() const
{
    return mSelectedKode;
}

bool MemberPilihViewModel::hasSelectedItem() const
{
    return mSelectedKode != -1;
}

QString MemberPilihViewModel::textQuery() const
{
    return mTextQuery;
}

void MemberPilihViewModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    emit textQueryChanged();
    refresh();
}

void MemberPilihViewModel::setSelectedIndex(int index)
{
    mSelectedIndex = index;
    refreshSelectedItem();
}

void MemberPilihViewModel::init()
{
    if (!mIsInitialized) {
        mIsInitialized = true;
        refresh();
    }
}

void MemberPilihViewModel::refresh()
{
    mList = mRepository->getAll(mTextQuery);

    emit listChanged();
    refreshSelectedItem();
}

void MemberPilihViewModel::refreshSelectedItem()
{
    if (mSelectedIndex < 0 || mSelectedIndex >= mList.count())
        mSelectedKode = -1;
    else mSelectedKode = mList.at(mSelectedIndex)->kode();

    emit selectedKodeChanged();
    emit hasSelectedItemChanged();

}
