#ifndef BOOKLISTDETAILMODEL_H
#define BOOKLISTDETAILMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QSqlQueryModel>

class BookListDetailModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString kode READ kode WRITE setKode NOTIFY kodeChanged)
    Q_PROPERTY(int jumlahBuku READ jumlahBuku NOTIFY kodeChanged)
    Q_PROPERTY(QString kodeKategori READ kodeKategori NOTIFY kodeChanged)
    Q_PROPERTY(QString kodePenerbit READ kodePenerbit NOTIFY kodeChanged)
    QML_ELEMENT
public:
    explicit BookListDetailModel(QObject *parent = nullptr);

    QString kode();
    void setKode(const QString &Id);

    int jumlahBuku();
    QString kodeKategori();
    QString kodePenerbit();

signals:
    void kodeChanged();

private:
    QString mKode;
    int mJumlahBuku;
    QString mKodeKategori;
    QString mKodePenerbit;
};

#endif // BOOKLISTDETAILMODEL_H
