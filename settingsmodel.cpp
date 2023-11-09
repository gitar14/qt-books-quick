#include "settingsmodel.h"
#include "sqlhelper.h"
#include <QSqlDatabase>

SettingsModel::SettingsModel(QObject *parent)
    : QObject{parent}
{

}

void SettingsModel::clearDatabase()
{
    QSqlDatabase db;
    SQLHelper::clearDatabase(db);
    SQLHelper::initializeDatabase(db);
}
