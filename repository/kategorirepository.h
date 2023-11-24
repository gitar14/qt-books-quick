#ifndef KATEGORIREPOSITORY_H
#define KATEGORIREPOSITORY_H

#include <Qt>
#include "list/kategorimodel.h"

class KategoriRepository : QObject
{
    Q_OBJECT
public:
    explicit KategoriRepository(QObject *parent = nullptr);

    KategoriModel* createListModel();
    void addNew(QString jenis);
    void edit(int kode, QString jenis);
    void remove(int kode);
signals:
    void dataChanged();
};

#endif // KATEGORIREPOSITORY_H
