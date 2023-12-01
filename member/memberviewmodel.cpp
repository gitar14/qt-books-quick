#include "memberviewmodel.h"

MemberViewModel::MemberViewModel(QObject *parent)
    : MemberPilihViewModel{parent}
{
    connect(this, SIGNAL(selectedKodeChanged()), this, SLOT(refreshSelectedData()));
    init();
}


MemberData *MemberViewModel::selectedData() const
{
    return mSelectedData.get();
}

void MemberViewModel::removeSelectedItem()
{
    mRepository->remove(mSelectedData->kode());
}

void MemberViewModel::refreshSelectedData()
{
    if (selectedKode() == -1)
        mSelectedData.reset(new MemberData());
    else mSelectedData.reset(mRepository->get(selectedKode()));

    emit selectedDataChanged();
}
