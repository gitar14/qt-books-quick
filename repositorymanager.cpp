#include "repositorymanager.h"
#include "repository/kategorirepository.h"
#include "repository/penerbitrepository.h"

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
