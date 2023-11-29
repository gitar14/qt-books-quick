#include "userbuatadminviewmodel.h"
#include "usecase/userusecase.h"

UserBuatAdminViewModel::UserBuatAdminViewModel(QObject *parent)
    : UserBaseEditViewModel{parent}

{

}

bool UserBuatAdminViewModel::isValid() const
{
    return idField()->isValid() && namaDepanField()->isValid()
           && namaBelakakngField()->isValid() && password()->isValid()
           && passwordUlang()->isValid();
}

void UserBuatAdminViewModel::submit()
{
    UserUseCase::addUser(mRepository,
                         idField()->value(),
                         namaDepanField()->value(),
                         namaBelakakngField()->value(),
                         password()->value(),
                         UserData::AdminRole);
}
