#include "kategoriviewmodel.h"
#include "repository/kategorirepository.h"
#include "repositorymanager.h"

KategoriViewModel::KategoriViewModel(QObject *parent)
    : QObject{parent}, mListModel{RepositoryManager::getInstance()->getKategori()->createListModel()}
{
    mListModel->setParent(this);
    connect(mListModel, SIGNAL(modelReset()), this, SLOT(refreshSelectedItem()));
}

KategoriModel *KategoriViewModel::listModel() const
{
    return mListModel;
}

void KategoriViewModel::setSelectedIndex(int index)
{
    mSelectedIndex = index;
    refreshSelectedItem();
}

int KategoriViewModel::selectedKode() const
{
    return mSelectedKode;
}

QString KategoriViewModel::selectedName() const
{
    return mSelectedName;
}

QString KategoriViewModel::textQuery() const
{
    return mTextQuery;
}

void KategoriViewModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    listModel()->setTextQuery(newTextQuery);
    emit textQueryChanged();
}

void KategoriViewModel::removeSelected()
{
    RepositoryManager::getInstance()->getKategori()->remove(mSelectedKode);
}

void KategoriViewModel::refreshSelectedItem()
{
    QModelIndex modelIndex = listModel()->index(mSelectedIndex, 0);
    QVariant kodeVariant = listModel()->data(modelIndex, KategoriModel::KodeRole);
    if (!kodeVariant.isNull()) {
        mSelectedKode = kodeVariant.toInt();
        mSelectedName = listModel()->data(modelIndex, KategoriModel::JenisRole).toString();
    } else {
        mSelectedKode = -1;
        mSelectedName = "";
    }
    emit selectedKodeChanged();
    emit selectedNameChanged();
}

bool KategoriViewModel::hasSelectedItem() const
{
    return mSelectedKode != -1;
}
