#include "penerbitviewmodel.h"
#include "repository/penerbitrepository.h"
#include "repositorymanager.h"

PenerbitViewModel::PenerbitViewModel(QObject *parent)
    : QObject{parent}, mListModel{RepositoryManager::getInstance()->getPenerbit()->createListModel()}
{
    mListModel->setParent(this);
    connect(mListModel, SIGNAL(modelReset()), this, SLOT(refreshSelectedItem()));
}

PenerbitModel *PenerbitViewModel::listModel() const
{
    return mListModel;
}

int PenerbitViewModel::selectedKode() const
{
    return mSelectedKode;
}

bool PenerbitViewModel::hasSelectedItem() const
{
    return mSelectedKode != -1;
}

QString PenerbitViewModel::selectedName() const
{
    return mSelectedName;
}

QString PenerbitViewModel::selectedAlamat() const
{
    return mSelectedAlamat;
}

void PenerbitViewModel::refreshSelectedItem()
{
    QModelIndex index = mListModel->index(mSelectedIndex, 0);
    QVariant kodeVar = mListModel->data(index, PenerbitModel::KodeRole);
    if (!kodeVar.isNull()) {
        mSelectedKode = kodeVar.toInt();
        mSelectedName = mListModel->data(index, PenerbitModel::NamaRole).toString();
        mSelectedAlamat = mListModel->data(index, PenerbitModel::AlamatRole).toString();
    } else {
        mSelectedKode = -1;
        mSelectedName = "";
        mSelectedAlamat = "";
    }

    emit selectedKodeChanged();
    emit selectedNameChanged();
    emit selectedAlamatChanged();
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
    mListModel->setTextQuery(mTextQuery);
    emit textQueryChanged();
}

void PenerbitViewModel::setSelectedIndex(int index)
{
    mSelectedIndex = index;
    refreshSelectedItem();
}

void PenerbitViewModel::removeSelected()
{
    RepositoryManager::getInstance()->getPenerbit()->remove(mSelectedKode);
}
