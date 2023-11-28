#include "settingviewmodel.h"
#include "repository/sqlhelper.h"
#include <QSqlDatabase>
#include "repositorymanager.h"

SettingViewModel::SettingViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getSetting()}
{
    mDendaPerHari = mRepository->getDendaPerHari();
}

SettingViewModel::~SettingViewModel()
{
    mRepository->setDendaPerHari(mDendaPerHari);
}

void SettingViewModel::clearDatabase()
{
    QSqlDatabase db;
    SQLHelper::clearDatabase(db);
    SQLHelper::initializeDatabase(db);
}

int SettingViewModel::dendaPerHari() const
{
    return mDendaPerHari;
}

void SettingViewModel::setDendaPerHari(int newDendaPerHari)
{
    if (mDendaPerHari == newDendaPerHari)
        return;
    mDendaPerHari = newDendaPerHari;
    emit dendaPerHariChanged();
}
