#ifndef MEMBERREPOSITORY_H
#define MEMBERREPOSITORY_H

#include <QObject>
#include <QDate>
#include "entity/member.h"

class MemberRepository : public QObject
{
    Q_OBJECT
public:
    explicit MemberRepository(QObject *parent = nullptr);

    QList<MemberData*> getAll(QString textQuery);
    MemberData* get(int kode);
    void add(QString namaDepan, QString namaBelakang, QDate tanggalLahir);
    void edit(int kode, QString namaDepan, QString namaBelakang, QDate tanggalLahir);
    void remove(int kode);

signals:
    void dataChanged();
};

#endif // MEMBERREPOSITORY_H
