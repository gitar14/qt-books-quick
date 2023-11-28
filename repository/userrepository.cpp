#include "userrepository.h"
#include "sqlhelper.h"
#include <QSqlQuery>
#include <QSqlError>


UserRepository::UserRepository(QObject *parent)
    : QObject{parent}
{

}

bool UserRepository::hasAvailableUser()
{
    QSqlQuery query;
    if (!query.exec("SELECT COUNT(id_user) > 0 FROM User"))
        qFatal() << "Cannot query for hasAvailableUser " << query.lastError().text();

    if (query.next())
        return query.value(0).toBool();

    return false;
}

QList<UserData *> UserRepository::getAllPegawai(QString textQuery)
{
    QHash<QString, QVariant> binds;
    QString queryString = "SELECT"
                          "   id_user,"
                          "   nama_depan_user, "
                          "   nama_belakang_user "
                          "FROM User "
                          "WHERE role = 1";
    if (textQuery.length()>0) {
        queryString += " AND (nama_depan_user || ' ' || nama_belakang_user) LIKE :textQuery";
        binds[":textQuery"]="%"+ textQuery +"%";
    }

    QSqlQuery query;
    query.prepare(queryString);
    SQLHelper::applyBindMaps(query, binds);

    if (!query.exec())
        qFatal("Cannot query User: %s", qPrintable(query.lastError().text()));

    QList<UserData*> result;

    while (query.next()) {
        result.append(new UserData(
                          query.value(0).toString(),
                          query.value(1).toString(),
                          query.value(2).toString(),
            query.value(3).toInt() == UserData::AdminRole ? UserData::AdminRole : UserData::PegawaiRole));
    }


    return result;
}

UserData *UserRepository::get(QString id)
{
    QSqlQuery query;
    query.prepare("SELECT "
                  " id_user,"
                  " nama_depan_user,"
                  " nama_belakang_user,"
                  " role "
                  "FROM User WHERE id_user = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        qFatal() << "Cannot query for login " << query.lastError().text() << query.lastError().driverText();

    return query.next() ? new UserData(
        query.value(0).toString(),
        query.value(1).toString(),
        query.value(2).toString(),
        query.value(3).toInt() == UserData::AdminRole ? UserData::AdminRole : UserData::PegawaiRole
               ) : new UserData();
}

QString UserRepository::getPasswordHash(QString id)
{
    QSqlQuery query;
    query.prepare("SELECT password_hash FROM User WHERE id_user = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        qFatal() << "Cannot get password for User " << query.lastError().text();

    return query.next() ? query.value(0).toString() : "";
}

void UserRepository::add(QString id, QString namaDepan, QString namaBelakang, QString passwordHash, UserData::UserRole role)
{
    QSqlQuery query;

    query.prepare("INSERT INTO User("
                  " id_user,"
                  " nama_depan_user,"
                  " nama_belakang_user,"
                  " role,"
                  " password_hash"
                  ") VALUES ("
                  " :id,"
                  " :nama_depan,"
                  " :nama_belakang,"
                  " :role,"
                  " :password_hash"
                  ")");
    query.bindValue(":id", id);
    query.bindValue(":nama_depan", namaDepan);
    query.bindValue(":nama_belakang", namaBelakang);
    query.bindValue(":role", role);
    query.bindValue(":password_hash", passwordHash);

    if (!query.exec())
        qFatal() << "Cannot create new user " << query.lastError().text();

    emit dataChanged();
}

void UserRepository::edit(QString id, QString namaDepan, QString namaBelakang)
{
    QSqlQuery query;

    query.prepare("UPDATE User SET "
                  " nama_depan_user = :namaDepan,"
                  " nama_belakang_user = :namaBelakang "
                  "WHERE id_user = :idUser");

    query.bindValue(":idUser", id);
    query.bindValue(":namaDepan", namaDepan);
    query.bindValue(":namaBelakang", namaBelakang);

    if (!query.exec())
        qFatal() << "Cannot edit User " << query.lastError().text();

    emit dataChanged();
}

void UserRepository::remove(QString id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM User WHERE id_user = :idUser");

    query.bindValue(":idUser", id);

    if (!query.exec())
        qFatal() << "Cannot remove User " << query.lastError().text();

    emit dataChanged();
}
