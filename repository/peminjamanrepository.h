#ifndef PEMINJAMANREPOSITORY_H
#define PEMINJAMANREPOSITORY_H

#include <QObject>
#include "entity/peminjaman.h"

class PeminjamanRepository : public QObject
{
    Q_OBJECT
public:
    explicit PeminjamanRepository(QObject *parent = nullptr);

    QList<PeminjamanData*> getList(PeminjamanData::StatusFilter statusFilter);
    PeminjamanDetailData* get(int kode);
    int add(int kodeMember, QString idUser, QDate tanggal, int lama);
    void update(int kode, int kodeMember, QDate tanggal, int lama);
    void remove(int kode);
    void tandaiDikembalikan(int kode, QString idUser, QDate tanggal, int dendaTerlambatPerBukuHari);
    void tandaiBelumDikembalikan(int kode);

    QList<PeminjamanBukuData*> getBukuList(int kode);
    void addAllBuku(int kode, QList<PeminjamanBukuData*> bukuList);
    void updateAllBuku(int kode, QList<PeminjamanBukuData*> bukuList);
    void removeAllBuku(int kode);
    void resetDendaBuku(int kode);

    int getJumlahBukuDipinjam(int kodeBuku);
signals:
    void dataChanged();
private:
    void internalUpdateAllBuku(int kode, QList<PeminjamanBukuData*> bukuList);

    static const QStringList bukuCandidateKey;
};

#endif // PEMINJAMANREPOSITORY_H
