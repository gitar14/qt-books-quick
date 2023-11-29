#include "settingrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonValue>
#include "sqlhelper.h"

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

const QStringList SettingRepository::tableCandidateKey = {"pengaturan_key"};

void SettingRepository::set(QString key, QVariant value)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(SQLHelper::createUpsertQuery(
        db,
        "Pengaturan("
        " pengaturan_key,"
        " pengaturan_value"
        ") VALUES ("
        " :key,"
        " :value"
        ")",
        "pengaturan_value = :value",
        tableCandidateKey
        ));
    query.bindValue(":key", key);
    query.bindValue(":value", value.toString());
    if (!query.exec())
        qFatal() << "Cannot update Pengaturan " << query.lastError().text() << query.lastQuery();
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
