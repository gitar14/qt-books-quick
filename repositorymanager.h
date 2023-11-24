#ifndef REPOSITORYMANAGER_H
#define REPOSITORYMANAGER_H

class KategoriRepository;

class RepositoryManager
{
private:
    RepositoryManager();

    KategoriRepository* mKategori = nullptr;
public:
    static RepositoryManager *getInstance();

    KategoriRepository* getKategori();
};

#endif // REPOSITORYMANAGER_H
