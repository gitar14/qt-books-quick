#include "userpegawaieditviewmodel.h"
#include "usecase/userusecase.h"

UserPegawaiEditViewModel::UserPegawaiEditViewModel(QObject *parent)
    : UserBaseEditViewModel{parent}
{

}

void UserPegawaiEditViewModel::configure(QString id)
{
    mIsNew = id == "";

    if (!mIsNew) {
        QScopedPointer<UserData> data(mRepository->get(id));
        idField()->setValue(data->id());
        namaDepanField()->setValue(data->namaDepan());
        namaBelakakngField()->setValue(data->namaBelakang());
    } else {
        idField()->setValue("");
        namaDepanField()->setValue("");
        namaBelakakngField()->setValue("");
    }

    password()->setValue("");
    passwordUlang()->setValue("");

    emit isNewChanged();
}

bool UserPegawaiEditViewModel::isValid() const
{
    return idField()->isValid() && namaDepanField()->isValid() && namaBelakakngField()->isValid()
           && (!mIsNew || (password()->isValid() && passwordUlang()->isValid()));
}

bool UserPegawaiEditViewModel::isNew() const
{
    return mIsNew;
}

void UserPegawaiEditViewModel::submit()
{
    if (mIsNew) {
        UserUseCase::addUser(mRepository, idField()->value(), namaDepanField()->value(), namaBelakakngField()->value(),
                             password()->value(), UserData::PegawaiRole);
    } else {
        mRepository->edit(idField()->value(), namaDepanField()->value(), namaBelakakngField()->value());
    }
}
