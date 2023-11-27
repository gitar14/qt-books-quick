#ifndef USERBUATADMINVIEWMODEL_H
#define USERBUATADMINVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "userbaseeditviewmodel.h"

class UserBuatAdminViewModel : public UserBaseEditViewModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit UserBuatAdminViewModel(QObject *parent = nullptr);

    bool isValid() const override;
    Q_INVOKABLE void submit();
};

#endif // USERBUATADMINVIEWMODEL_H
