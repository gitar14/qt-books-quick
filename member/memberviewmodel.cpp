#include "memberviewmodel.h"

MemberViewModel::MemberViewModel(QObject *parent)
    : MemberPilihViewModel{parent}, mSelectedData{nullptr}
{
    connect(this, SIGNAL(selectedKodeChanged()), this, SLOT(refreshSelectedData()));
    refresh();
}


MemberData *MemberViewModel::selectedData() const
{
    return mSelectedData;
}

void MemberViewModel::removeSelectedItem()
{
    mRepository->remove(mSelectedData->kode());
}

void MemberViewModel::refreshSelectedData()
{
    MemberData* prevData = mSelectedData;
    if (selectedKode() == -1)
        mSelectedData = new MemberData();
    else mSelectedData =  mRepository->get(selectedKode());
    mSelectedData->setParent(this);

    emit selectedDataChanged();

    if (prevData != nullptr)
        delete prevData;
}
