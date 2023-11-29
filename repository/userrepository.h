#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QObject>
#include "entity/user.h"

class UserRepository : public QObject
{
    Q_OBJECT
public:
    explicit UserRepository(QObject *parent = nullptr);

    bool hasAvailableUser();

    QList<UserData*> getAllPegawai(QString textQuery);
    UserData* get(QString id);
    QString getPasswordHash(QString id);
    void add(QString id, QString namaDepan, QString namaBelakang, QString passwordHash, UserData::UserRole role);
    void edit(QString id, QString namaDepan, QString namaBelakang);
    void remove(QString id);
signals:
    void dataChanged();
};

#endif // USERREPOSITORY_H
