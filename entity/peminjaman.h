#ifndef PEMINJAMAN_H
#define PEMINJAMAN_H

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
    Q_PROPERTY(QString namaMember READ namaMember CONSTANT)
    Q_PROPERTY(QDate tenggatPengembalian READ tenggatPengembalian CONSTANT)
    Q_PROPERTY(bool sudahDikembalikan READ sudahDikembalikan CONSTANT)
public:
    enum StatusFilter {
        SemuaStatus = 0,
        BelumDikembalikanStatus,
        MelewatiTenggatStatus,
        SudahDikembalikanStatus
    };
    Q_ENUM(StatusFilter)

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

    QString namaMember() const;
    QDate tenggatPengembalian() const;
    bool sudahDikembalikan() const;

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

class PeminjamanDetailData : public PeminjamanData {
    Q_OBJECT
    Q_PROPERTY(QString peminjamanUserId READ peminjamanUserId CONSTANT FINAL)
    Q_PROPERTY(QString peminjamanUserNamaDepan READ peminjamanUserNamaDepan CONSTANT FINAL)
    Q_PROPERTY(QString peminjamanUserNamaBelakang READ peminjamanUserNamaBelakang CONSTANT FINAL)
    Q_PROPERTY(QString pengembalianUserId READ pengembalianUserId CONSTANT FINAL)
    Q_PROPERTY(QString pengembalianUserNamaDepan READ pengembalianUserNamaDepan CONSTANT FINAL)
    Q_PROPERTY(QString pengembalianUserNamaBelakang READ pengembalianUserNamaBelakang CONSTANT FINAL)
    Q_PROPERTY(QString peminjamanUserNama READ peminjamanUserNama CONSTANT FINAL)
    Q_PROPERTY(QString pengembalianUserNama READ pengembalianUserNama CONSTANT FINAL)
public:
    PeminjamanDetailData(int kode = -1,
                         int kodeMember = -1,
                         const QString &namaDepanMember = "",
                         const QString &namaBelakangMember = "",
                         const QDate &tanggalPeminjaman = QDate(),
                         int lamaPeminjaman = 0,
                         const QDate &tanggalPengembalian = QDate(),
                         int dendaTerlambatPerBuku = 0,
                         const QString &peminjamanUserId = "",
                         const QString &peminjamanUserNamaDepan = "",
                         const QString &peminjamanUserNamaBelakang = "",
                         const QString &pengembalianUserId = "",
                         const QString &pengembalianUserNamaDepan = "",
                         const QString &pengembalianUserNamaBelakang = "");

    QString peminjamanUserId() const;
    QString peminjamanUserNamaDepan() const;
    QString peminjamanUserNamaBelakang() const;
    QString pengembalianUserId() const;
    QString pengembalianUserNamaDepan() const;
    QString pengembalianUserNamaBelakang() const;

    QString peminjamanUserNama() const;
    QString pengembalianUserNama() const;
private:
    QString mPeminjamanUserId;
    QString mPeminjamanUserNamaDepan;
    QString mPeminjamanUserNamaBelakang;
    QString mPengembalianUserId;
    QString mPengembalianUserNamaDepan;
    QString mPengembalianUserNamaBelakang;
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


#endif // PEMINJAMAN_H
