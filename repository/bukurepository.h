#ifndef BUKUREPOSITORY_H
#define BUKUREPOSITORY_H

#include <QObject>

class BukuData: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int kode READ kode CONSTANT)
    Q_PROPERTY(QString judul READ judul CONSTANT)
    Q_PROPERTY(QString penulis READ penulis CONSTANT)
    Q_PROPERTY(int jumlahHilang READ jumlahHilang CONSTANT)
    Q_PROPERTY(int tahunTerbit READ tahunTerbit CONSTANT)
    Q_PROPERTY(int kodeKategori READ kodeKategori CONSTANT)
    Q_PROPERTY(QString namaKategori READ namaKategori CONSTANT)
    Q_PROPERTY(int kodePenerbit READ kodePenebit CONSTANT)
    Q_PROPERTY(QString namaPenerbit READ namaPenerbit CONSTANT)
public:
    explicit BukuData(int kode = -1,
                      QString judul = "",
                      QString penulis = "",
                      int jumlahHilang = 0,
                      int tahunTerbit = 0,
                      int kodeKategori = -1,
                      QString namaKategori = "",
                      int kodePenerbit = -1,
                      QString namaPenerbit = "");
    int kode() const;
    QString judul() const;
    QString penulis() const;
    int jumlahHilang() const;
    int tahunTerbit() const;
    int kodeKategori() const;
    QString namaKategori() const;
    int kodePenebit() const;
    QString namaPenerbit() const;

private:
    int mKode;
    QString mJudul;
    QString mPenulis;
    int mJumlahHilang;
    int mTahunTerbit;
    int mKodeKategori;
    QString mNamaKategori;
    int mKodePenerbit;
    QString mNamaPenerbit;
};

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
