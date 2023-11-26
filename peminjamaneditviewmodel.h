#ifndef PEMINJAMANEDITVIEWMODEL_H
#define PEMINJAMANEDITVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/peminjamanrepository.h"

class PeminjamanEditViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isNew READ isNew NOTIFY isNewChanged)
    Q_PROPERTY(int kodeMember READ kodeMember WRITE setKodeMember NOTIFY kodeMemberChanged FINAL)
    Q_PROPERTY(QString namaMember READ namaMember NOTIFY namaMemberChanged FINAL)
    Q_PROPERTY(QDate tanggalPeminjaman READ tanggalPeminjaman WRITE setTanggalPeminjaman NOTIFY tanggalPeminjamanChanged FINAL)
    Q_PROPERTY(int lamaPeminjaman READ lamaPeminjaman WRITE setLamaPeminjaman NOTIFY lamaPeminjamanChanged FINAL)
    Q_PROPERTY(QList<PeminjamanBukuData *> bukuList READ bukuList NOTIFY bukuListChanged FINAL)
    Q_PROPERTY(QList<int> kodeBukuList READ kodeBukuList NOTIFY kodeBukuListChanged FINAL)
    Q_PROPERTY(int isBukuAvailable READ isBukuAvailable NOTIFY isBukuAvailableChanged FINAL)
    QML_ELEMENT
public:
    explicit PeminjamanEditViewModel(QObject *parent = nullptr);

    Q_INVOKABLE void configure(int kode = -1);

    bool isNew() const;
    int kodeMember() const;
    void setKodeMember(int newKodeMember);
    QString namaMember() const;
    QDate tanggalPeminjaman() const;
    void setTanggalPeminjaman(const QDate &newTanggalPeminjaman);
    int lamaPeminjaman() const;
    void setLamaPeminjaman(int newLamaPeminjaman);
    QList<PeminjamanBukuData *> bukuList() const;

    Q_INVOKABLE void appendBuku(int kodeBuku);
    Q_INVOKABLE void removeBuku(int index);

    QList<int> kodeBukuList() const;
    int isBukuAvailable() const;

    Q_INVOKABLE void submit();

signals:
    void isNewChanged();
    void kodeMemberChanged();
    void namaMemberChanged();
    void tanggalPeminjamanChanged();
    void lamaPeminjamanChanged();
    void bukuListChanged();
    void kodeBukuListChanged();
    void isBukuAvailableChanged();

private:
    PeminjamanRepository* mRepository;

    int mKode;
    int mKodeMember;
    QString mNamaMember;
    QDate mTanggalPeminjaman;
    int mLamaPeminjaman;
    QList<PeminjamanBukuData*> mBukuList;
    QList<int> mKodeBukuList;
    int mIsBukuAvailable;

    void refreshAvailableBuku();
};

#endif // PEMINJAMANEDITVIEWMODEL_H
