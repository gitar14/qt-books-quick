#ifndef BOOKLISTDETAILMODEL_H
#define BOOKLISTDETAILMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QSqlQueryModel>

class BookListDetailModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString bookId READ bookId WRITE setBookId NOTIFY bookIdChanged)
    Q_PROPERTY(QString judul READ judul NOTIFY bookIdChanged)
    Q_PROPERTY(QString penulis READ penulis NOTIFY bookIdChanged)
    Q_PROPERTY(int jumlahBuku READ jumlahBuku NOTIFY bookIdChanged)
    Q_PROPERTY(QString kodePenerbit READ kodePenerbit NOTIFY bookIdChanged)
    Q_PROPERTY(QString namaPenerbit READ namaPenerbit NOTIFY bookIdChanged)
    QML_ELEMENT
public:
    explicit BookListDetailModel(QObject *parent = nullptr);

    QString bookId();
    void setBookId(const QString &Id);

    QString judul();
    QString penulis();
    int jumlahBuku();
    QString kodePenerbit();
    QString namaPenerbit();

signals:
    void bookIdChanged();

private:
    QString mBookId;
    QString mJudul;
    QString mPenulis;
    int mJumlahBuku;
    QString mKodePenerbit;
    QString mNamaPenerbit;
};

#endif // BOOKLISTDETAILMODEL_H
