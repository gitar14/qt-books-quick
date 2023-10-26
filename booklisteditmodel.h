#ifndef BOOKLISTEDITMODEL_H
#define BOOKLISTEDITMODEL_H

#include <QObject>
#include <QQmlEngine>

class BookListEditModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString bookId READ bookId WRITE setBookId NOTIFY bookIdChanged)
    Q_PROPERTY(QString judul READ judul WRITE setJudul NOTIFY judulChanged)
    Q_PROPERTY(QString penulis READ penulis WRITE setPenulis NOTIFY penulisChanged)
    Q_PROPERTY(int jumlahBuku READ jumlahBuku WRITE setJumlahBuku NOTIFY jumlahBukuChanged)
    Q_PROPERTY(int penerbitIndex READ penerbitIndex WRITE setPenerbitIndex NOTIFY penerbitIndexChanged)
    Q_PROPERTY(QStringList penerbitList READ penerbitList NOTIFY penerbitListChanged)
    QML_ELEMENT
public:
    explicit BookListEditModel(QObject *parent = nullptr);

    QString bookId();
    void setBookId(QString Id);

    Q_INVOKABLE void setIsNew();

    QString judul();
    QString penulis();
    int jumlahBuku();
    int penerbitIndex();
    QStringList penerbitList();

    void setJudul(QString judul);
    void setPenulis(QString penulis);
    void setJumlahBuku(int jumlah);
    void setPenerbitIndex(int index);

    Q_INVOKABLE void submit();
signals:
    void bookIdChanged();
    void judulChanged();
    void penulisChanged();
    void jumlahBukuChanged();
    void penerbitIndexChanged();
    void penerbitListChanged();

private:
    QString mBookId;
    QString mJudul;
    QString mPenulis;
    int mJumlahBuku;
    QString mPenerbitKode;
    QMap<QString, QString> mPenerbitList;
    int mPenerbitIndex;
};

#endif // BOOKLISTEDITMODEL_H
