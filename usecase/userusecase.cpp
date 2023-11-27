#include "userusecase.h"
#include <botan/system_rng.h>
#include <botan/bcrypt.h>

void UserUseCase::addUser(UserRepository* repository, QString id, QString namaDepan, QString namaBelakang, QString password, UserData::UserRole role)
{
    QString passwordHash = QString::fromStdString(Botan::generate_bcrypt(password.toStdString(), Botan::system_rng(), 10));
    repository->add(id, namaDepan, namaBelakang, passwordHash, role);
}

bool UserUseCase::checkUserPassword(UserRepository *repository, QString id, QString password)
{
    QString passwordHash = repository->getPasswordHash(id);
    return Botan::check_bcrypt(
        password.toStdString(),
        passwordHash.toStdString());
}
