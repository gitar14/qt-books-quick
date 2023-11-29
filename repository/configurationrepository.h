#ifndef CONFIGURATIONREPOSITORY_H
#define CONFIGURATIONREPOSITORY_H

#include <QObject>
#include <QJsonObject>

class ConfigurationRepository : public QObject
{
    Q_OBJECT
public:
    explicit ConfigurationRepository(QObject *parent = nullptr);
    ~ConfigurationRepository();

    QVariant get(QString key);
    void set(QString key, QVariant value);
private:

    QString mConfigLocation;
    QJsonObject mData;

    void load();
    void save();

};

#endif // CONFIGURATIONREPOSITORY_H
