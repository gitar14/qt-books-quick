#ifndef PEMINJAMANREPOSITORY_H
#define PEMINJAMANREPOSITORY_H

#include <QObject>
#include <QDate>

class PeminjamanData : public QObject {
    Q_OBJECT
    Q_PROPERTY(int kode READ kode CONSTANT FINAL)
    Q_PROPERTY(int kodeMember READ kodeMember CONSTANT FINAL)
    Q_PROPERTY(QString namaDepanMember READ namaDepanMember CONSTANT FINAL)
    Q_PROPERTY(QString namaBelakangMember READ namaBelakangMember CONSTANT FINAL)
    Q_PROPERTY(QDate tanggalPeminjaman READ tanggalPeminjaman CONSTANT FINAL)
    Q_PROPERTY(int lamaPeminjaman READ lamaPeminjaman CONSTANT FINAL)
    Q_PROPERTY(QDate tanggalPengembalian READ tanggalPengembalian CONSTANT FINAL)
    Q_PROPERTY(int dendaTerlambatPerBuku READ dendaTerlambatPerBuku CONSTANT FINAL)
public:
    PeminjamanData(
        int kode = -1,
        int kodeMember = -1,
        QString namaDepanMember = "",
        QString namaBelakangMember = "",
        QDate tanggalPeminjaman = QDate(),
        int lamaPeminjaman = 0,
        QDate tanggalPengembalian = QDate(),
        int dendaTerlambatPerBuku = 0
        );

    int kode() const;
    int kodeMember() const;
    QString namaDepanMember() const;
    QString namaBelakangMember() const;
    QDate tanggalPeminjaman() const;
    int lamaPeminjaman() const;
    QDate tanggalPengembalian() const;
    int dendaTerlambatPerBuku() const;

private:
    int mKode;
    int mKodeMember;
    QString mNamaDepanMember;
    QString mNamaBelakangMember;
    QDate mTanggalPeminjaman;
    int mLamaPeminjaman;
    QDate mTanggalPengembalian;
    int mDendaTerlambatPerBuku;
};

class PeminjamanBukuData : public QObject {
    Q_OBJECT
    Q_PROPERTY(int kodeBuku READ kodeBuku CONSTANT FINAL)
    Q_PROPERTY(QString judul READ judul CONSTANT FINAL)
    Q_PROPERTY(int denda READ denda WRITE setDenda NOTIFY dendaChanged FINAL)
public:
    PeminjamanBukuData(int kodeBuku, QString judul, int denda);
    int kodeBuku() const;
    QString judul() const;
    int denda() const;

    void setDenda(int newDenda);

signals:
    void dendaChanged();

private:
    int mKodeBuku;
    QString mJudul;
    int mDenda;
};


class PeminjamanRepository : public QObject
{
    Q_OBJECT
public:
    explicit PeminjamanRepository(QObject *parent = nullptr);

    enum StatusFilter {
        SemuaStatus = 0,
        BelumDikembalikanStatus,
        MelewatiTenggatStatus,
        SudahDikembalikanStatus
    };

    QList<PeminjamanData*> getList(StatusFilter statusFilter);
    PeminjamanData* get(int kode);
    int add(int kodeMember, QString idUser, QDate tanggal, int lama);
    void update(int kode, int kodeMember, QDate tanggal, int lama);
    void remove(int kode);
    void tandaiDikembalikan(int kode, QDate tanggal, int dendaTerlambatPerBukuHari);
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
};

#endif // PEMINJAMANREPOSITORY_H
