#ifndef USERLOGINVIEWMODEL_H
#define USERLOGINVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "textfielddata.h"
#include "repository/userrepository.h"

class UserLoginViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TextFieldData *idField READ idField CONSTANT FINAL)
    Q_PROPERTY(TextFieldData *passwordField READ passwordField CONSTANT FINAL)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
    Q_PROPERTY(QString errorText READ errorText NOTIFY errorTextChanged)
    QML_ELEMENT
public:
    explicit UserLoginViewModel(QObject *parent = nullptr);

    TextFieldData *idField() const;
    TextFieldData *passwordField() const;

    bool isValid() const;

    Q_INVOKABLE bool login();

    QString errorText() const;

signals:
    void isValidChanged();
    void errorTextChanged();

private:
    UserRepository* mRepository;
    TextFieldData* mIdField;
    TextFieldData* mPasswordField;
    bool m_isValid;
    QString mErrorText;
};

#endif // USERLOGINVIEWMODEL_H
