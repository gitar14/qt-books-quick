#ifndef BUKU_H
#define BUKU_H

#include <QObject>

class BukuData: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int kode READ kode CONSTANT)
    Q_PROPERTY(QString judul READ judul CONSTANT)
    Q_PROPERTY(QString penulis READ penulis CONSTANT)
    Q_PROPERTY(int kodeKategori READ kodeKategori CONSTANT)
    Q_PROPERTY(QString namaKategori READ namaKategori CONSTANT)

public:
    explicit BukuData(int kode = -1,
                      QString judul = "",
                      QString penulis = "",
                      int kodeKategori = -1,
                      QString namaKategori = "");
    int kode() const;
    QString judul() const;
    QString penulis() const;

    int kodeKategori() const;
    QString namaKategori() const;


private:
    int mKode;
    QString mJudul;
    QString mPenulis;
    int mKodeKategori;
    QString mNamaKategori;
};

class BukuDetailData : public BukuData {
    Q_OBJECT
    Q_PROPERTY(int kodePenerbit READ kodePenebit CONSTANT)
    Q_PROPERTY(QString namaPenerbit READ namaPenerbit CONSTANT)
    Q_PROPERTY(int jumlahHilang READ jumlahHilang CONSTANT)
    Q_PROPERTY(int tahunTerbit READ tahunTerbit CONSTANT)
public:
    BukuDetailData(int kode = -1,
                   QString judul = "",
                   QString penulis = "",
                   int jumlahHilang = 0,
                   int tahunTerbit = 0,
                   int kodeKategori = -1,
                   QString namaKategori = "",
                   int kodePenerbit = -1,
                   QString namaPenerbit = "");

    int kodePenebit() const;
    QString namaPenerbit() const;
    int jumlahHilang() const;
    int tahunTerbit() const;
private:
    int mKodePenerbit;
    QString mNamaPenerbit;
    int mJumlahHilang;
    int mTahunTerbit;
};

#endif // BUKU_H
