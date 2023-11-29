#ifndef PENGADAAN_H
#define PENGADAAN_H

#include <QObject>
#include <QDate>

class PengadaanData : public QObject {
    Q_OBJECT
    Q_PROPERTY(int kode READ kode CONSTANT FINAL)
    Q_PROPERTY(QString sumber READ sumber CONSTANT FINAL)
    Q_PROPERTY(QDate tanggalPengadaan READ tanggalPengadaan CONSTANT FINAL)
public:
    PengadaanData(int kode = -1, QString sumber = "", QDate tanggalPengadaan = QDate());
    int kode() const;
    QString sumber() const;
    QDate tanggalPengadaan() const;

private:
    int mKode;
    QString mSumber;
    QDate mTanggalPengadaan;
};

class PengadaanDetailData : public PengadaanData {
    Q_OBJECT
    Q_PROPERTY(QString userId READ userId CONSTANT FINAL)
    Q_PROPERTY(QString userNamaDepan READ userNamaDepan CONSTANT FINAL)
    Q_PROPERTY(QString userNamaBelakang READ userNamaBelakang CONSTANT FINAL)
    Q_PROPERTY(QString userNama READ userNama CONSTANT FINAL)
public:
    PengadaanDetailData(
        int kode = -1,
        const QString &sumber = "",
        const QDate &tanggalPengadaan = QDate(),
        QString userId = "",
        const QString &userNamaDepan = "",
        const QString &userNamaBelakang = "");

    QString userId() const;
    QString userNamaDepan() const;
    QString userNamaBelakang() const;

    QString userNama() const;

private:
    QString mUserId;
    QString mUserNamaDepan;
    QString mUserNamaBelakang;
};

class PengadaanBukuData : public QObject {
    Q_OBJECT
    Q_PROPERTY(int kodeBuku READ kodeBuku CONSTANT)
    Q_PROPERTY(int jumlah READ jumlah WRITE setJumlah NOTIFY jumlahChanged FINAL)
    Q_PROPERTY(QString judul READ judul CONSTANT)
public:
    PengadaanBukuData(int kodeBuku, int jumlah, QString judul);

    int kodeBuku() const;
    int jumlah() const;
    void setJumlah(int newJumlah);
    QString judul() const;

signals:
    void jumlahChanged();

private:
    int mKodeBuku;
    int mJumlah;
    QString mJudul;
};

#endif // PENGADAAN_H
