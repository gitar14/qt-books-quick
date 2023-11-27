#include "memberviewmodel.h"

MemberViewModel::MemberViewModel(QObject *parent)
    : MemberPilihViewModel{parent}
{
    connect(this, SIGNAL(selectedKodeChanged()), this, SLOT(refreshSelectedData()));
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
    if (selectedKode() == -1)
        mSelectedData = new MemberData();
    else mSelectedData =  mRepository->get(selectedKode());

    emit selectedDataChanged();
}
