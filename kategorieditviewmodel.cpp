#include "kategorieditviewmodel.h"
#include "repository/kategorirepository.h"
#include "repositorymanager.h"

KategoriEditViewModel::KategoriEditViewModel(QObject *parent)
    : QObject{parent}, mNamaField{new TextFieldData(this)}
{
    mNamaField->setName("Nama");
    mNamaField->setMaxLength(25);
    connect(mNamaField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
}

void KategoriEditViewModel::configure(int kode, QString nama)
{
    setKode(kode);
    mNamaField->setValue(nama);
}

int KategoriEditViewModel::kode() const
{
    return mKode;
}

void KategoriEditViewModel::setKode(int newKode)
{
    if (mKode == newKode)
        return;
    mKode = newKode;
    emit kodeChanged();
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
