#include "configurationrepository.h"
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QJsonDocument>

ConfigurationRepository::ConfigurationRepository(QObject *parent)
    : QObject{parent}
{
    mConfigLocation = QStandardPaths::locate(QStandardPaths::AppDataLocation, "config.json");

    if (mConfigLocation.isEmpty()) {
        mConfigLocation = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0] + "/config.json";
    }

    load();
}

ConfigurationRepository::~ConfigurationRepository()
{
    save();
}

QVariant ConfigurationRepository::get(QString key)
{
    return mData.value(key).toVariant();
}

void ConfigurationRepository::set(QString key, QVariant value)
{
    mData[key] = QJsonValue::fromVariant(value);
}


void ConfigurationRepository::load()
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

void ConfigurationRepository::save()
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
