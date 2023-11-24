#ifndef PENERBITREPOSITORY_H
#define PENERBITREPOSITORY_H

#include <QObject>
#include "list/penerbitmodel.h"

class PenerbitRepository : public QObject
{
    Q_OBJECT
public:
    explicit PenerbitRepository(QObject *parent = nullptr);

    PenerbitModel* createListModel();
    void add(QString nama, QString alamat);
    void edit(int kode, QString nama, QString alamat);
    void remove(int kode);

signals:
    void dataChanged();
};

#endif // PENERBITREPOSITORY_H
