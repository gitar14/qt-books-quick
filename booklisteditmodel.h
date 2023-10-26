#ifndef BOOKLISTEDITMODEL_H
#define BOOKLISTEDITMODEL_H

#include <QObject>
#include <QQmlEngine>

class BookListEditModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString kode READ kode WRITE setKodeId NOTIFY kodeChanged)
    Q_PROPERTY(QString judul READ judul WRITE setJudul NOTIFY judulChanged)
    Q_PROPERTY(QString penulis READ penulis WRITE setPenulis NOTIFY penulisChanged)
    Q_PROPERTY(int jumlahBuku READ jumlahBuku WRITE setJumlahBuku NOTIFY jumlahBukuChanged)
    Q_PROPERTY(int kategoriIndex READ kategoriIndex WRITE setKategoriIndex NOTIFY kategoriIndexChanged)
    Q_PROPERTY(QStringList kategoriList READ kategoriList NOTIFY kategoriListChanged)
    Q_PROPERTY(int tahunTerbit READ tahunTerbit WRITE setTahunTerbit NOTIFY tahunTerbitChanged)
    QML_ELEMENT
public:
    explicit BookListEditModel(QObject *parent = nullptr);

    QString kode();
    void setKodeId(QString Id);

    Q_INVOKABLE void setIsNew();

    QString judul();
    QString penulis();
    int jumlahBuku();
    int kategoriIndex();
    QStringList kategoriList();

    void setJudul(QString judul);
    void setPenulis(QString penulis);
    void setJumlahBuku(int jumlah);
    void setKategoriIndex(int index);

    Q_INVOKABLE void submit();
    int tahunTerbit() const;
    void setTahunTerbit(int newTahunTerbit);

signals:
    void kodeChanged();
    void judulChanged();
    void penulisChanged();
    void jumlahBukuChanged();
    void kategoriIndexChanged();
    void kategoriListChanged();

    void tahunTerbitChanged();

private:
    QString mKode;
    QString mJudul;
    QString mPenulis;
    int mJumlahBuku;
    QString mKodeKategori;
    QMap<QString, QString> mKategoriList;
    int mKategoriIndex;
    int mTahunTerbit;
};

#endif // BOOKLISTEDITMODEL_H
