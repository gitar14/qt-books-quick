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
    if (index == mSelectedIndex)
        return;

    mSelectedIndex = index;
    emit selectedIndexChanged();
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
    mList = mRepository->getAll(mIgnoredKode, mTextQuery);

    emit listChanged();
    refreshSelectedItem();
}

void MemberPilihViewModel::setIgnoredKode(const QList<int> &newIgnoredKode)
{
    if (mIgnoredKode == newIgnoredKode)
        return;
    mIgnoredKode = newIgnoredKode;
    emit ignoredKodeChanged();
    refresh();
}

QList<int> MemberPilihViewModel::ignoredKode() const
{
    return mIgnoredKode;
}

void MemberPilihViewModel::refreshSelectedItem()
{
    if (mSelectedIndex < 0 || mSelectedIndex >= mList.count())
        mSelectedKode = -1;
    else mSelectedKode = mList.at(mSelectedIndex)->kode();

    emit selectedKodeChanged();
    emit hasSelectedItemChanged();

}

void MemberPilihViewModel::setSelectedKode(int newSelectedKode)
{
    if (mSelectedKode == newSelectedKode)
        return;
    mSelectedKode = newSelectedKode;

    int index = -1;
    for (int i = 0; i < mList.length(); i++) {
        if (mList.at(i)->kode() == newSelectedKode) {
            index = i;
            break;
        }
    }
    mSelectedIndex = index;

    emit selectedKodeChanged();
    emit selectedIndexChanged();
    emit hasSelectedItemChanged();
}

int MemberPilihViewModel::selectedIndex() const
{
    return mSelectedIndex;
}
