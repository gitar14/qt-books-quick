#include "kategorieditviewmodel.h"
#include "repository/kategorirepository.h"
#include "repositorymanager.h"

KategoriEditViewModel::KategoriEditViewModel(QObject *parent)
    : QObject{parent}
{

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

QString KategoriEditViewModel::nama() const
{
    return mNama;
}

void KategoriEditViewModel::setNama(const QString &newNama)
{
    if (mNama == newNama)
        return;
    mNama = newNama;
    emit namaChanged();
}

int KategoriEditViewModel::namaMaxlength() const
{
    return 25;
}

int KategoriEditViewModel::namaAvailableLength() const
{
    return namaMaxlength() - mNama.length();
}

QString KategoriEditViewModel::namaError() const
{
    if (mNama.length() == 0) return "Nama tidak boleh kosong";
    return "";
}

void KategoriEditViewModel::submit()
{
    KategoriRepository* repository = RepositoryManager::getInstance()->getKategori();
    if (mKode == -1) {
        repository->addNew(mNama);
    }  else {
        repository->edit(mKode, mNama);
    }
}
