#include "settingrepository.h"
#include <QSqlQuery>
#include <QSqlError>

SettingRepository::SettingRepository(QObject *parent)
    : QObject{parent}
{

}

#define DENDA_PERHARI_KEY "dendaPerHari"

void SettingRepository::setDendaPerHari(int denda)
{
    set(DENDA_PERHARI_KEY, denda);
}

int SettingRepository::getDendaPerHari()
{
    return get(DENDA_PERHARI_KEY).toInt();
}

void SettingRepository::set(QString key, QVariant value)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Pengaturan("
                  " pengaturan_key,"
                  " pengaturan_value"
                  ") VALUES ("
                  " :key,"
                  " :value"
                  ") ON CONFLICT("
                  " pengaturan_key"
                  ") DO UPDATE "
                  "SET pengaturan_value = :value");
    query.bindValue(":key", key);
    query.bindValue(":value", value);
    if (!query.exec())
        qFatal() << "Cannot update Pengaturan " << query.lastError().text();
}

QVariant SettingRepository::get(QString key)
{
    QSqlQuery query;
    query.prepare("SELECT pengaturan_value "
                  "FROM Pengaturan "
                  "WHERE pengaturan_key = :key");
    query.bindValue(":key", key);

    if (!query.exec())
        qFatal() << "Cannot get pengaturan " << query.lastError().text();

    return query.next() ? query.value(0) : QVariant();
}
