#ifndef BOOKLISTDETAILMODEL_H
#define BOOKLISTDETAILMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QSqlQueryModel>

class BookListDetailModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int kode READ kode WRITE setKode NOTIFY kodeChanged)
    Q_PROPERTY(int jumlahPengadaan READ jumlahPengadaan NOTIFY kodeChanged)
    Q_PROPERTY(int jumlahHilang READ jumlahHilang NOTIFY kodeChanged)
    Q_PROPERTY(int jumlahDipinjam READ jumlahDipinjam NOTIFY kodeChanged)
    Q_PROPERTY(int kodeKategori READ kodeKategori NOTIFY kodeChanged)
    Q_PROPERTY(int kodePenerbit READ kodePenerbit NOTIFY kodeChanged)
    QML_ELEMENT
public:
    explicit BookListDetailModel(QObject *parent = nullptr);

    int kode();
    void setKode(const int &id);

    int jumlahPengadaan() const;
    int jumlahHilang() const;
    int jumlahDipinjam() const;
    int kodeKategori();
    int kodePenerbit();

signals:
    void kodeChanged();

private:
    int mKode;
    int mKodeKategori;
    int mKodePenerbit;
    int mJumlahPengadaan;
    int mJumlahHilang;
    int mJumlahDipinjam;
};

#endif // BOOKLISTDETAILMODEL_H
