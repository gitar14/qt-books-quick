#ifndef REPOSITORYMANAGER_H
#define REPOSITORYMANAGER_H

#include <QObject>

class ConfigurationRepository;
class KategoriRepository;
class PenerbitRepository;
class BukuRepository;
class PengadaanRepository;
class PeminjamanRepository;
class MemberRepository;
class UserRepository;
class SettingRepository;

class RepositoryManager : QObject
{
    Q_OBJECT
private:
    RepositoryManager();

    ConfigurationRepository* mConfiguration = nullptr;
    KategoriRepository* mKategori = nullptr;
    PenerbitRepository* mPenerbit = nullptr;
    BukuRepository* mBuku = nullptr;
    PengadaanRepository* mPengadaan = nullptr;
    PeminjamanRepository* mPeminjaman = nullptr;
    MemberRepository* mMember = nullptr;
    UserRepository* mUser = nullptr;
    SettingRepository* mSetting = nullptr;
public:
    static RepositoryManager *getInstance();

    ConfigurationRepository* getConfiguration();
    KategoriRepository* getKategori();
    PenerbitRepository* getPenerbit();
    BukuRepository* getBuku();
    PengadaanRepository* getPengadaan();
    PeminjamanRepository* getPeminjaman();
    MemberRepository* getMember();
    UserRepository* getUser();
    SettingRepository* getSetting();
};

#endif // REPOSITORYMANAGER_H
