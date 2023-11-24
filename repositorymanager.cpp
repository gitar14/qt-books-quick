#include "repositorymanager.h"
#include "./repository/kategorirepository.h"

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
