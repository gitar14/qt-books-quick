#include "membereditviewmodel.h"
#include "repositorymanager.h"

MemberEditViewModel::MemberEditViewModel(QObject *parent)
    : QObject{parent},
    mNamaDepanField{new TextFieldData(this)},
    mNamaBelakangField{new TextFieldData(this)},
    mRepository{RepositoryManager::getInstance()->getMember()}
{
    mNamaDepanField->setMaxLength(25);
    mNamaBelakangField->setMaxLength(25);

    connect(mNamaDepanField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
    connect(mNamaBelakangField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
}

void MemberEditViewModel::configure(int kode)
{
    mKode = kode;

    MemberData* data = mRepository->get(mKode);

    mNamaDepanField->setValue(data->namaDepan());
    mNamaBelakangField->setValue(data->namaBelakang());
    if (data->tanggalLahir().isValid())
        setTanggalLahir(data->tanggalLahir());
    else setTanggalLahir(QDate::currentDate());

    delete data;

    emit isNewChanged();
    emit isValidChanged();
}

TextFieldData *MemberEditViewModel::namaDepanField() const
{
    return mNamaDepanField;
}

TextFieldData *MemberEditViewModel::namaBelakangField() const
{
    return mNamaBelakangField;
}

QDate MemberEditViewModel::tanggalLahir() const
{
    return mTanggalLahir;
}

void MemberEditViewModel::setTanggalLahir(const QDate &newTanggalLahir)
{
    if (mTanggalLahir == newTanggalLahir)
        return;
    mTanggalLahir = newTanggalLahir;
    emit tanggalLahirChanged();
}

bool MemberEditViewModel::isNew() const
{
    return mKode == -1;
}

bool MemberEditViewModel::isValid() const
{
    return mNamaDepanField->isValid() && mNamaBelakangField->isValid();
}

void MemberEditViewModel::submit()
{
    if (mKode == -1)
        mRepository->add(mNamaDepanField->value(), mNamaBelakangField->value(), mTanggalLahir);
    else
        mRepository->edit(mKode, mNamaDepanField->value(), mNamaBelakangField->value(), mTanggalLahir);
}
