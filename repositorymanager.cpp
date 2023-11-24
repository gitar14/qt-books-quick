#include "repositorymanager.h"
#include "repository/bukurepository.h"
#include "repository/kategorirepository.h"
#include "repository/penerbitrepository.h"
#include "repository/pengadaanrepository.h"
#include "repository/peminjamanrepository.h"

RepositoryManager::RepositoryManager()
{

}

RepositoryManager* RepositoryManager::getInstance()
{
    static RepositoryManager instance;
    return &instance;
}

KategoriRepository *RepositoryManager::getKategori()
{
    if (mKategori == nullptr) {
        mKategori = new KategoriRepository();
    }
    return mKategori;
}

PenerbitRepository *RepositoryManager::getPenerbit()
{
    if (mPenerbit == nullptr) {
        mPenerbit = new PenerbitRepository();
    }
    return mPenerbit;
}

BukuRepository *RepositoryManager::getBuku()
{
    if (mBuku == nullptr) {
        mBuku = new BukuRepository();
    }
    return mBuku;
}

PengadaanRepository *RepositoryManager::getPengadaan()
{
    if (mPengadaan == nullptr) {
        mPengadaan = new PengadaanRepository();
    }
    return mPengadaan;
}

PeminjamanRepository *RepositoryManager::getPeminjaman()
{
    if (mPeminjaman == nullptr) {
        mPeminjaman = new PeminjamanRepository();
    }
    return mPeminjaman;
}
