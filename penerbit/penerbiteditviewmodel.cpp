#include "penerbiteditviewmodel.h"
#include "repositorymanager.h"

PenerbitEditViewModel::PenerbitEditViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getPenerbit()},
    mNamaField{new TextFieldData(this)},
    mAlamatField{new TextFieldData(this)}
{
    mNamaField->setMaxLength(25);
    mAlamatField->setMaxLength(30);

    connect(mNamaField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
    connect(mAlamatField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
}

void PenerbitEditViewModel::configure(int kode)
{
    PenerbitData* data = mRepository->get(kode);

    mKode = data->kode();
    mNamaField->setValue(data->nama());
    mAlamatField->setValue(data->alamat());

    delete data;

    emit isNewChanged();
}

TextFieldData *PenerbitEditViewModel::namaField() const
{
    return mNamaField;
}

TextFieldData *PenerbitEditViewModel::alamatField() const
{
    return mAlamatField;
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
