#ifndef BOOKLISTDETAILMODEL_H
#define BOOKLISTDETAILMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QSqlQueryModel>

class BookListDetailModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString kode READ kode WRITE setKode NOTIFY kodeChanged)
    Q_PROPERTY(QString judul READ judul NOTIFY kodeChanged)
    Q_PROPERTY(QString penulis READ penulis NOTIFY kodeChanged)
    Q_PROPERTY(int jumlahBuku READ jumlahBuku NOTIFY kodeChanged)
    Q_PROPERTY(QString kodeKategori READ kodeKategori NOTIFY kodeChanged)
    Q_PROPERTY(QString jenis READ jenis NOTIFY kodeChanged)
    Q_PROPERTY(int tahunTerbit READ tahunTerbit NOTIFY kodeChanged)
    QML_ELEMENT
public:
    explicit BookListDetailModel(QObject *parent = nullptr);

    QString kode();
    void setKode(const QString &Id);

    QString judul();
    QString penulis();
    int jumlahBuku();
    QString kodeKategori();
    QString jenis();
    int tahunTerbit() const;

signals:
    void kodeChanged();

private:
    QString mKode;
    QString mJudul;
    QString mPenulis;
    int mJumlahBuku;
    QString mKodeKategori;
    QString mJenis;
    int mTahunTerbit;
};

#endif // BOOKLISTDETAILMODEL_H
