#include "settingsmodel.h"
#include "sqlhelper.h"
#include <QSqlDatabase>
#include "sqlhelper.h"

SettingsModel::SettingsModel(QObject *parent)
    : QObject{parent}
{
    mDendaPerHari = SQLHelper::getDendaPerHari();
}

SettingsModel::~SettingsModel()
{
    SQLHelper::setDendaPerHari(mDendaPerHari);
}

void SettingsModel::clearDatabase()
{
    QSqlDatabase db;
    SQLHelper::clearDatabase(db);
    SQLHelper::initializeDatabase(db);
}

int SettingsModel::dendaPerHari() const
{
    return mDendaPerHari;
}

void SettingsModel::setDendaPerHari(int newDendaPerHari)
{
    if (mDendaPerHari == newDendaPerHari)
        return;
    mDendaPerHari = newDendaPerHari;
    emit dendaPerHariChanged();
}
