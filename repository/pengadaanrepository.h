#ifndef PENGADAANREPOSITORY_H
#define PENGADAANREPOSITORY_H

#include <QObject>
#include <QDate>
#include "entity/pengadaan.h"

class PengadaanRepository : public QObject
{
    Q_OBJECT
public:
    explicit PengadaanRepository(QObject *parent = nullptr);

    QList<PengadaanData *> getList(QString textQuery);
    PengadaanDetailData* get(int kode);
    int add(QString sumber, QString idUser, QDate tanggalPengadaan);
    void update(int kode, QString sumber);
    void remove(int kode);
    int getJumlahPengadaanBuku(int kodeBuku);

    QList<PengadaanBukuData*> getBukuList(int kode);
    void updateAllBuku(int kode, QList<PengadaanBukuData*> list);
    void addAllBuku(int kode, QList<PengadaanBukuData*> list);
    void removeAllBuku(int kode);
private:
    void interalUpdateAllBuku(int kode, QList<PengadaanBukuData*> list);
signals:
    void dataChanged();
};

#endif // PENGADAANREPOSITORY_H
