#include "usermanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <botan/system_rng.h>
#include <botan/bcrypt.h>

UserManager::UserManager(QObject *parent)
    : QObject{parent}
{

}

bool UserManager::hasAvailableUser()
{
    QSqlQuery query;
    if (!query.exec("SELECT COUNT(id_user) > 0 FROM User"))
        qFatal() << "Cannot query for hasAvailableUser " << query.lastError().text();

    if (query.next())
        return query.value(0).toBool();

    return false;
}

void UserManager::addUser(QString id, QString namaDepan, QString namaBelakang, UserRole role, QString password)
{
    QString passwordHash = QString::fromStdString(Botan::generate_bcrypt(password.toStdString(), Botan::system_rng(), 10));
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

    emit userAdded();
}

void UserManager::login(QString id, QString password)
{
    QSqlQuery query;

    query.prepare("SELECT "
                  " nama_depan_user,"
                  " nama_belakang_user,"
                  " password_hash,"
                  " role "
                  "FROM User WHERE id_user = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        qFatal() << "Cannot query for login " << query.lastError().text() << query.lastError().driverText();

    if (!query.next()) {
        emit loginFailed("User tidak ada");
        return;
    }

    QString passwordHash = query.value("password_hash").toString();

    if (!Botan::check_bcrypt(
            password.toStdString(),
            passwordHash.toStdString())) {
        emit loginFailed("Password salah");
        return;
    }

    mLoggedUserId = id;
    mLoggedUserName =  QStringLiteral("%1 %2").arg(
        query.value("nama_depan_user").toString(),
        query.value("nama_belakang_user").toString());
    mLoggedUserRole = (UserRole) query.value("role").toInt();

    emit loggedIn();
    emit loggedUserChanged();
}

UserManager *UserManager::getInstance()
{
    static UserManager instance;
    return &instance;
}

UserManager::UserRole UserManager::loggedUserRole() const
{
    return mLoggedUserRole;
}

QString UserManager::loggedUserName() const
{
    return mLoggedUserName;
}

QString UserManager::loggedUserId() const
{
    return mLoggedUserId;
}
