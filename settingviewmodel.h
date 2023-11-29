#ifndef SETTINGVIEWMODEL_H
#define SETTINGVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/settingrepository.h"

class SettingViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int dendaPerHari READ dendaPerHari WRITE setDendaPerHari NOTIFY dendaPerHariChanged)
    QML_ELEMENT
public:
    explicit SettingViewModel(QObject *parent = nullptr);
    ~SettingViewModel();

    Q_INVOKABLE void clearDatabase();
    int dendaPerHari() const;
    void setDendaPerHari(int newDendaPerHari);

signals:

    void dendaPerHariChanged();
private:
    SettingRepository* mRepository;
    int mDendaPerHari;
};

#endif // SETTINGVIEWMODEL_H
