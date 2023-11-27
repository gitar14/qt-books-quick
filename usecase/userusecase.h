#ifndef USERUSECASE_H
#define USERUSECASE_H

#include "repository/userrepository.h"

namespace UserUseCase {
    void addUser(UserRepository* repository, QString id, QString namaDepan, QString namaBelakang, QString password, UserData::UserRole role);
    bool checkUserPassword(UserRepository *repository, QString id, QString password);
}

#endif // USERUSECASE_H
