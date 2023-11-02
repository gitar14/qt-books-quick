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
    QML_ELEMENT
public:
    explicit BookListDetailModel(QObject *parent = nullptr);

    QString kode();
    void setKode(const QString &Id);

    int jumlahBuku();
    QString kodeKategori();

signals:
    void kodeChanged();

private:
    QString mKode;
    int mJumlahBuku;
    QString mKodeKategori;
};

#endif // BOOKLISTDETAILMODEL_H
