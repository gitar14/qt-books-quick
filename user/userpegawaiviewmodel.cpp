#include "userpegawaiviewmodel.h"
#include "repositorymanager.h"

UserPegawaiViewModel::UserPegawaiViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getUser()}
{
    refresh();
    connect(mRepository, SIGNAL(dataChanged()), this, SLOT(refresh()));
}

QList<UserData *> UserPegawaiViewModel::list() const
{
    return mList;
}

QString UserPegawaiViewModel::textQuery() const
{
    return mTextQuery;
}

void UserPegawaiViewModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    emit textQueryChanged();
    refresh();
}

void UserPegawaiViewModel::setSelectedIndex(int newSelectedIndex)
{
    mSelectedIndex = newSelectedIndex;
    refreshSelectedItem();
}

UserData *UserPegawaiViewModel::selectedData() const
{
    return mSelectedData;
}

void UserPegawaiViewModel::refresh()
{
    mList = mRepository->getAllPegawai(mTextQuery);

    emit listChanged();
    refreshSelectedItem();
}

void UserPegawaiViewModel::refreshSelectedItem()
{
    if (mSelectedIndex < 0 || mSelectedIndex >= mList.count())
        mSelectedData = new UserData();
    else mSelectedData = mRepository->get(mList.at(mSelectedIndex)->id());

    emit selectedDataChanged();
    emit hasSelectedItemChanged();
}

bool UserPegawaiViewModel::hasSelectedItem() const
{
    return mSelectedData->id() != "";
}
