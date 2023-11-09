#include "configurationmanager.h"
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDir>
#include <QStack>

ConfigurationManager::~ConfigurationManager()
{
    save();
}

ConfigurationManager *ConfigurationManager::getInstance()
{
    static ConfigurationManager instance;
    return &instance;
}

QVariant ConfigurationManager::get(QString key)
{
    return mData.value(key).toVariant();
}

void ConfigurationManager::set(QString key, QVariant value)
{
    mData[key] = QJsonValue::fromVariant(value);
}

ConfigurationManager::ConfigurationManager()
{
    mConfigLocation = QStandardPaths::locate(QStandardPaths::AppDataLocation, "config.json");

    if (mConfigLocation.isEmpty()) {
        mConfigLocation = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0] + "/config.json";
    }

    load();
}

void ConfigurationManager::load()
{
    QFile file(mConfigLocation);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray bytes = file.readAll();

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(bytes, &error);

        if (error.error != QJsonParseError::NoError) {
            qInfo() << "Config file have error " << error.errorString();
            return;
        }

        if (!doc.isObject()) {
            qInfo() << "Config file is not object";
            return;
        }


        mData = doc.object();
    }
}

void ConfigurationManager::save()
{
    QDir().mkdir(QFileInfo(mConfigLocation).dir().path());

    QFile file(mConfigLocation);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonDocument document(mData);
        QByteArray bytes = document.toJson();

        file.write(bytes, bytes.size());

        file.close();
    } else {
        qWarning() << "Cannot save configuration";
    }
}
