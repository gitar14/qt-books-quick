#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QObject>
#include <QQmlEngine>

class SettingsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int dendaPerHari READ dendaPerHari WRITE setDendaPerHari NOTIFY dendaPerHariChanged)
    QML_ELEMENT
public:
    explicit SettingsModel(QObject *parent = nullptr);
    ~SettingsModel();

    Q_INVOKABLE void clearDatabase();
    int dendaPerHari() const;
    void setDendaPerHari(int newDendaPerHari);

signals:

    void dendaPerHariChanged();
private:
    int mDendaPerHari;
};

#endif // SETTINGSMODEL_H
