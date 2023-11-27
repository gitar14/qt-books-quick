#include "bukueditviewmodel.h"
#include "repositorymanager.h"
#include "repository/kategorirepository.h"
#include "repository/penerbitrepository.h"
#include "repository/bukurepository.h"
#include "sqlhelper.h"

BukuEditViewModel::BukuEditViewModel(QObject *parent)
    : QObject{parent},
    mJudulField{new TextFieldData(this)},
    mPenulisField{new TextFieldData(this)},
    mKategoriField{new ComboFieldData(this)},
    mPenerbitField{new ComboFieldData(this)}
{
    mJudulField->setName("Judul");
    mJudulField->setMaxLength(25);
    mPenulisField->setName("Penulis");
    mPenulisField->setMaxLength(25);
    mKategoriField->setName("Kategori");
    mPenerbitField->setName("Penerbit");

    connect(mJudulField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
    connect(mPenulisField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
    connect(mKategoriField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
    connect(mPenerbitField, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
}

BukuEditViewModel::~BukuEditViewModel()
{
    qDeleteAll(mKategoriList);
    qDeleteAll(mPenerbitList);
}

void BukuEditViewModel::configure(int kode)
{
    BukuData* data = kode == -1 ? new BukuData() :
                         RepositoryManager::getInstance()->getBuku()->getBukuData(kode);

    mKode = kode;
    mJudulField->setValue(data->judul());
    mPenulisField->setValue(data->penulis());
    mJumlahHilang = data->jumlahHilang();
    mTahunTerbit = data->tahunTerbit();

    QList<KategoriData*> prevKategoriList = mKategoriList;
    mKategoriList = RepositoryManager::getInstance()->getKategori()->getAll("");
    emit kategoriListChanged();

    int kategoriIndex = -1;
    for (int i = 0; i < mKategoriList.length(); i++) {
        if (mKategoriList.at(i)->kode() == data->kodeKategori()) {
            kategoriIndex = i;
            break;
        }
    }
    mKategoriField->setIndex(kategoriIndex);

    QList<PenerbitData*> prevPenerbitList = mPenerbitList;
    mPenerbitList = RepositoryManager::getInstance()->getPenerbit()->getAll("");
    emit penerbitListChanged();

    int penerbitIndex = -1;
    for (int i = 0; i < mPenerbitList.length(); i++) {
        if (mPenerbitList.at(i)->kode() == data->kodePenebit()) {
            penerbitIndex = i;
            break;
        }
    }
    mPenerbitField->setIndex(penerbitIndex);

    emit jumlahHilangChanged();
    emit tahunTerbitChanged();
    emit isNewChanged();

    qDeleteAll(prevKategoriList);
    qDeleteAll(prevPenerbitList);

    delete data;
}

TextFieldData *BukuEditViewModel::judulField() const
{
    return mJudulField;
}

TextFieldData *BukuEditViewModel::penulisField() const
{
    return mPenulisField;
}

int BukuEditViewModel::jumlahHilang() const
{
    return mJumlahHilang;
}

void BukuEditViewModel::jumlahHilang(int newJumlahHilang)
{
    if (mJumlahHilang == newJumlahHilang)
        return;
    mJumlahHilang = newJumlahHilang;
    emit jumlahHilangChanged();
}

int BukuEditViewModel::tahunTerbit() const
{
    return mTahunTerbit;
}

void BukuEditViewModel::setTahunTerbit(int newTahunTerbit)
{
    if (mTahunTerbit == newTahunTerbit)
        return;
    mTahunTerbit = newTahunTerbit;
    emit tahunTerbitChanged();
}

bool BukuEditViewModel::isNew() const
{
    return mKode == -1;
}

ComboFieldData *BukuEditViewModel::kategoriField() const
{
    return mKategoriField;
}

ComboFieldData *BukuEditViewModel::penerbitField() const
{
    return mPenerbitField;
}

bool BukuEditViewModel::isValid() const
{
    return mJudulField->isValid() && mPenulisField->isValid() && mKategoriField->isValid() && mPenerbitField->isValid();
}

void BukuEditViewModel::submit()
{
    BukuRepository* repository = RepositoryManager::getInstance()->getBuku();
    int kodeKategori = mKategoriList.at(mKategoriField->index())->kode();
    int kodePenerbit = mPenerbitList.at(mPenerbitField->index())->kode();
    if (mKode == -1)
        repository->addNew(mJudulField->value(), mPenulisField->value(), mTahunTerbit, kodeKategori, kodePenerbit);
    else
        repository->edit(mKode, mJudulField->value(), mPenulisField->value(), mJumlahHilang, mTahunTerbit, kodeKategori, kodePenerbit);
}

QList<KategoriData *> BukuEditViewModel::kategoriList() const
{
    return mKategoriList;
}

QList<PenerbitData *> BukuEditViewModel::penerbitList() const
{
    return mPenerbitList;
}
