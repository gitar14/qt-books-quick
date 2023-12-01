#include "kategorieditviewmodel.h"
#include "repositorymanager.h"

KategoriEditViewModel::KategoriEditViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getKategori()},
    mNamaField{new TextFieldData(this)}
{
    mNamaField->setMaxLength(25);
    connect(mNamaField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
}

void KategoriEditViewModel::configure(int kode)
{
    QScopedPointer<KategoriData> data(kode != - 1 ? mRepository->get(kode) : new KategoriData());
    mKode = data->kode();
    mNamaField->setValue(data->nama());

    emit isNewChanged();
}

void KategoriEditViewModel::submit()
{
    KategoriRepository* repository = RepositoryManager::getInstance()->getKategori();
    if (mKode == -1) {
        repository->addNew(mNamaField->value());
    }  else {
        repository->edit(mKode, mNamaField->value());
    }
}

TextFieldData *KategoriEditViewModel::namaField() const
{
    return mNamaField;
}

bool KategoriEditViewModel::isValid() const
{
    return mNamaField->isValid();
}

bool KategoriEditViewModel::isNew() const
{
    return mKode == -1;
}
