#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QObject>
#include <QQmlEngine>

class SettingsModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit SettingsModel(QObject *parent = nullptr);

    Q_INVOKABLE void clearDatabase();
signals:

};

#endif // SETTINGSMODEL_H
