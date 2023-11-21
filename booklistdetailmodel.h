#ifndef BOOKLISTDETAILMODEL_H
#define BOOKLISTDETAILMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QSqlQueryModel>

class BookListDetailModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int kode READ kode WRITE setKode NOTIFY kodeChanged)
    Q_PROPERTY(int jumlahBuku READ jumlahBuku NOTIFY kodeChanged)
    Q_PROPERTY(int kodeKategori READ kodeKategori NOTIFY kodeChanged)
    Q_PROPERTY(int kodePenerbit READ kodePenerbit NOTIFY kodeChanged)
    QML_ELEMENT
public:
    explicit BookListDetailModel(QObject *parent = nullptr);

    int kode();
    void setKode(const int &id);

    int jumlahBuku();
    int kodeKategori();
    int kodePenerbit();

signals:
    void kodeChanged();

private:
    int mKode;
    int mJumlahBuku;
    int mKodeKategori;
    int mKodePenerbit;
};

#endif // BOOKLISTDETAILMODEL_H
