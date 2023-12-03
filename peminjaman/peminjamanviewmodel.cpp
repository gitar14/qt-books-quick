#include "peminjamanviewmodel.h"
#include "repositorymanager.h"

PeminjamanViewModel::PeminjamanViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getPeminjaman()},
    mSelectedDenda{new PeminjamanDendaCalculator(this)}
{
    connect(mRepository, SIGNAL(dataChanged()), this, SLOT(refresh()));
    refresh();
}

QList<PeminjamanData *> PeminjamanViewModel::list() const
{
    return mList;
}

QString PeminjamanViewModel::textQuery() const
{
    return mTextQuery;
}

void PeminjamanViewModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    emit textQueryChanged();
    refresh();
}

PeminjamanData::StatusFilter PeminjamanViewModel::statusFilter() const
{
    return mStatusFilter;
}

void PeminjamanViewModel::setStatusFilter(PeminjamanData::StatusFilter newStatusFilter)
{
    if (mStatusFilter == newStatusFilter)
        return;
    mStatusFilter = newStatusFilter;
    emit statusFilterChanged();
    refresh();
}

void PeminjamanViewModel::refresh()
{
    mList = mRepository->getList(mStatusFilter, mTextQuery);

    emit listChanged();

    refreshSelectedItem();
}

PeminjamanDendaCalculator *PeminjamanViewModel::selectedDenda() const
{
    return mSelectedDenda;
}

void PeminjamanViewModel::tandaiBelumDikembalikanSelected()
{
    int kode = mSelectedData->kode();
    mRepository->tandaiBelumDikembalikan(kode);
    mRepository->resetDendaBuku(kode);
}

void PeminjamanViewModel::removeSelectedItem()
{
    int kode = mSelectedData->kode();
    mRepository->remove(kode);
    mRepository->removeAllBuku(kode);
}

QList<PeminjamanBukuData *> PeminjamanViewModel::selectedBukuList() const
{
    return mSelectedBukuList;
}

PeminjamanDetailData *PeminjamanViewModel::selectedData() const
{
    return mSelectedData.get();
}


void PeminjamanViewModel::refreshSelectedItem()
{
    int kode = -1;
    if (mSelectedIndex >= 0 && mSelectedIndex < mList.length())
        kode = mList.at(mSelectedIndex)->kode();

    mSelectedData.reset(mRepository->get(kode));

    mSelectedDenda->setDendaTerlambatPerBuku(mSelectedData->dendaTerlambatPerBuku());
    mSelectedDenda->setTenggatPengembalian(mSelectedData->tenggatPengembalian());
    mSelectedDenda->setTanggalPengembalian(mSelectedData->tanggalPengembalian());

    mSelectedBukuList = mRepository->getBukuList(kode);
    mSelectedDenda->setBukuList(mSelectedBukuList);

    emit selectedDataChanged();
    emit hasSelectedItemChanged();
    emit selectedBukuListChanged();
}

bool PeminjamanViewModel::hasSelectedItem() const
{
    return mSelectedData->kode() != -1;
}

void PeminjamanViewModel::setSelectedIndex(int index)
{
    mSelectedIndex = index;
    refreshSelectedItem();
}
