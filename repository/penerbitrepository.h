#ifndef PENERBITREPOSITORY_H
#define PENERBITREPOSITORY_H

#include <QObject>
#include "entity/penerbit.h"

class PenerbitRepository : public QObject
{
    Q_OBJECT
public:
    explicit PenerbitRepository(QObject *parent = nullptr);

    QList<PenerbitData*> getAll(QString textQuery);
    PenerbitDetailData *get(int kode);
    void add(QString nama, QString alamat);
    void edit(int kode, QString nama, QString alamat);
    void remove(int kode);

signals:
    void dataChanged();
};

#endif // PENERBITREPOSITORY_H
