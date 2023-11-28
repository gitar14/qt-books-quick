#ifndef KATEGORIREPOSITORY_H
#define KATEGORIREPOSITORY_H

#include <Qt>
#include <QObject>
#include "entity/kategori.h"

class KategoriRepository : public QObject
{
    Q_OBJECT
public:
    explicit KategoriRepository(QObject *parent = nullptr);

    QList<KategoriData*> getAll(QString textQuery);
    KategoriData* get(int kode);
    void addNew(QString jenis);
    void edit(int kode, QString jenis);
    void remove(int kode);
signals:
    void dataChanged();
};

#endif // KATEGORIREPOSITORY_H
