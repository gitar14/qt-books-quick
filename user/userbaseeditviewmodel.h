#ifndef USERBASEEDITVIEWMODEL_H
#define USERBASEEDITVIEWMODEL_H

#include <QObject>
#include "textfielddata.h"
#include "repository/userrepository.h"

class UserBaseEditViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TextFieldData *idField READ idField CONSTANT FINAL)
    Q_PROPERTY(TextFieldData *namaDepanField READ namaDepanField CONSTANT FINAL)
    Q_PROPERTY(TextFieldData *namaBelakakngField READ namaBelakakngField CONSTANT FINAL)
    Q_PROPERTY(TextFieldData *password READ password CONSTANT FINAL)
    Q_PROPERTY(TextFieldData *passwordUlang READ passwordUlang CONSTANT FINAL)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)

public:
    explicit UserBaseEditViewModel(QObject *parent = nullptr);

    TextFieldData *idField() const;
    TextFieldData *namaDepanField() const;
    TextFieldData *namaBelakakngField() const;
    TextFieldData *password() const;
    TextFieldData *passwordUlang() const;

    virtual bool isValid() const = 0;
signals:
    void isValidChanged();

protected:
    UserRepository *mRepository;

private:
    TextFieldData* mIdField;
    TextFieldData* mNamaDepanField;
    TextFieldData* mNamaBelakakngField;
    TextFieldData* mPassword;
    TextFieldData* mPasswordUlang;
};

#endif // USERBASEEDITVIEWMODEL_H
