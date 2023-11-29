#ifndef SETTINGREPOSITORY_H
#define SETTINGREPOSITORY_H

#include <QObject>

class SettingRepository : public QObject
{
    Q_OBJECT
public:
    explicit SettingRepository(QObject *parent = nullptr);

    void setDendaPerHari(int denda);
    int getDendaPerHari();
signals:

private:
    void set(QString key, QVariant value);
    QVariant get(QString key);

    static const QStringList tableCandidateKey;
};

#endif // SETTINGREPOSITORY_H
