#include "repositorymanager.h"
#include "repository/configurationrepository.h"
#include "repository/bukurepository.h"
#include "repository/kategorirepository.h"
#include "repository/penerbitrepository.h"
#include "repository/pengadaanrepository.h"
#include "repository/peminjamanrepository.h"
#include "repository/memberrepository.h"
#include "repository/userrepository.h"
#include "repository/settingrepository.h"
#include <QDebug>

RepositoryManager::RepositoryManager() : QObject()
{

}

RepositoryManager* RepositoryManager::getInstance()
{
    static RepositoryManager instance;
    return &instance;
}

ConfigurationRepository *RepositoryManager::getConfiguration()
{
    if (mConfiguration == nullptr) {
        mConfiguration = new ConfigurationRepository(this);
    }
    return mConfiguration;
}

KategoriRepository *RepositoryManager::getKategori()
{
    if (mKategori == nullptr) {
        mKategori = new KategoriRepository(this);
    }
    return mKategori;
}

PenerbitRepository *RepositoryManager::getPenerbit()
{
    if (mPenerbit == nullptr) {
        mPenerbit = new PenerbitRepository(this);
    }
    return mPenerbit;
}

BukuRepository *RepositoryManager::getBuku()
{
    if (mBuku == nullptr) {
        mBuku = new BukuRepository(this);
    }
    return mBuku;
}

PengadaanRepository *RepositoryManager::getPengadaan()
{
    if (mPengadaan == nullptr) {
        mPengadaan = new PengadaanRepository(this);
    }
    return mPengadaan;
}

PeminjamanRepository *RepositoryManager::getPeminjaman()
{
    if (mPeminjaman == nullptr) {
        mPeminjaman = new PeminjamanRepository(this);
    }
    return mPeminjaman;
}

MemberRepository *RepositoryManager::getMember()
{
    if (mMember == nullptr) {
        mMember = new MemberRepository(this);
    }
    return mMember;
}

UserRepository *RepositoryManager::getUser()
{
    if (mUser == nullptr) {
        mUser = new UserRepository(this);
    }
    return mUser;
}

SettingRepository *RepositoryManager::getSetting()
{
    if (mSetting == nullptr) {
        mSetting = new SettingRepository(this);
    }
    return mSetting;
}
