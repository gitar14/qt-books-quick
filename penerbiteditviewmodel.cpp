#include "penerbiteditviewmodel.h"
#include "repository/penerbitrepository.h"
#include "repositorymanager.h"

PenerbitEditViewModel::PenerbitEditViewModel(QObject *parent)
    : QObject{parent}, mNamaField{new TextFieldData(this)}, mAlamatField{new TextFieldData(this)}
{
    mNamaField->setName("Nama");
    mNamaField->setMaxLength(25);
    mAlamatField->setName("Alamat");
    mAlamatField->setMaxLength(30);

    connect(mNamaField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
    connect(mAlamatField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
}

void PenerbitEditViewModel::configure(int kode, QString nama, QString alamat)
{
    setKode(kode);
    mNamaField->setValue(nama);
    mAlamatField->setValue(alamat);
}

TextFieldData *PenerbitEditViewModel::namaField() const
{
    return mNamaField;
}

TextFieldData *PenerbitEditViewModel::alamatField() const
{
    return mAlamatField;
}

int PenerbitEditViewModel::kode() const
{
    return mKode;
}

void PenerbitEditViewModel::setKode(int newKode)
{
    if (mKode == newKode)
        return;
    mKode = newKode;
    emit kodeChanged();
}

bool PenerbitEditViewModel::isValid() const
{
    return mNamaField->isValid() && mAlamatField->isValid();
}

bool PenerbitEditViewModel::isNew() const
{
    return mKode == -1;
}

void PenerbitEditViewModel::submit()
{
    PenerbitRepository* repository = RepositoryManager::getInstance()->getPenerbit();
    if (isNew()) {
        repository->add(mNamaField->value(), mAlamatField->value());
    } else {
        repository->edit(mKode, mNamaField->value(), mAlamatField->value());
    }
}
