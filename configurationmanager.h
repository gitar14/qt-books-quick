#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include <QString>
#include <QJsonObject>

class ConfigurationManager
{
public:
    ~ConfigurationManager();

    static ConfigurationManager* getInstance();

    QVariant get(QString key);
    void set(QString key, QVariant value);
private:
    ConfigurationManager();

    QString mConfigLocation;
    QJsonObject mData;

    void load();
    void save();
};

#endif // CONFIGURATIONMANAGER_H
