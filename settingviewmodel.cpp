#include "settingviewmodel.h"
#include "repository/sqlhelper.h"
#include <QSqlDatabase>
#include "repositorymanager.h"
#include "usermanager.h"

SettingViewModel::SettingViewModel(QObject *parent)
    : QObject{parent},
    mRepository{RepositoryManager::getInstance()->getSetting()},
    mCanChangeDenda{UserManager::getInstance()->loggedUser()->role() == UserData::AdminRole}
{
    mDendaPerHari = mRepository->getDendaPerHari();
}

SettingViewModel::~SettingViewModel()
{
    if (mCanChangeDenda)
        mRepository->setDendaPerHari(mDendaPerHari);
}

void SettingViewModel::clearDatabase()
{
    QSqlDatabase db = QSqlDatabase::database();
    SQLHelper::clearDatabase(db);
    SQLHelper::initializeDatabase(db);
}

int SettingViewModel::dendaPerHari() const
{
    return mDendaPerHari;
}

void SettingViewModel::setDendaPerHari(int newDendaPerHari)
{
    if (!mCanChangeDenda)
        qFatal() << "Non admin user must not change denda";
    if (mDendaPerHari == newDendaPerHari)
        return;
    mDendaPerHari = newDendaPerHari;
    emit dendaPerHariChanged();
}

bool SettingViewModel::canChangeDenda() const
{
    return mCanChangeDenda;
}
