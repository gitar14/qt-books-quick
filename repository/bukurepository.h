#ifndef BUKUREPOSITORY_H
#define BUKUREPOSITORY_H

#include <QObject>
#include "entity/buku.h"

class BukuRepository : public QObject
{
    Q_OBJECT
public:
    explicit BukuRepository(QObject *parent = nullptr);

    QList<BukuData*> getList(QList<int> ignoredKode, QString textQuery, int kategoriFilter, int penerbitFiter);
    BukuData *getBukuData(int kode);
    void addNew(
        QString judul,
        QString penulis,
        int tahunTerbit,
        int kodeKategori,
        int kodePenerbit
        );
    void edit(
        int kode,
        QString judul,
        QString penulis,
        int jumlahHilang,
        int tahunTerbit,
        int kodeKategori,
        int kodePenerbit
        );
    void remove(int kode);
    bool isBookAvailable(QList<int> ignoredKode);
signals:
    void dataChanged();
};

#endif // BUKUREPOSITORY_H
