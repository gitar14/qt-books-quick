#ifndef REPOSITORYMANAGER_H
#define REPOSITORYMANAGER_H

class KategoriRepository;
class PenerbitRepository;

class RepositoryManager
{
private:
    RepositoryManager();

    KategoriRepository* mKategori = nullptr;
    PenerbitRepository* mPenerbit = nullptr;
public:
    static RepositoryManager *getInstance();

    KategoriRepository* getKategori();
    PenerbitRepository* getPenerbit();
};

#endif // REPOSITORYMANAGER_H
