#ifndef USERPEGAWAIEDITVIEWMODEL_H
#define USERPEGAWAIEDITVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "userbaseeditviewmodel.h"

class UserPegawaiEditViewModel : public UserBaseEditViewModel
{
    Q_OBJECT
    Q_PROPERTY(bool isNew READ isNew NOTIFY isNewChanged FINAL)
    QML_ELEMENT
public:
    explicit UserPegawaiEditViewModel(QObject *parent = nullptr);

    Q_INVOKABLE void configure(QString id = "");

    bool isValid() const override;
    bool isNew() const;

    Q_INVOKABLE void submit();

signals:

    void isNewChanged();

private:
    bool mIsNew;
};

#endif // USERPEGAWAIEDITVIEWMODEL_H
