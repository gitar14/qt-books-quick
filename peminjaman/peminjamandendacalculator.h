#ifndef PEMINJAMANDENDACALCULATOR_H
#define PEMINJAMANDENDACALCULATOR_H

#include <QObject>
#include <QQmlEngine>
#include "repository/peminjamanrepository.h"

class PeminjamanDendaCalculator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDate tenggatPengembalian
               READ tenggatPengembalian
               WRITE setTenggatPengembalian
               NOTIFY tenggatPengembalianChanged)
    Q_PROPERTY(QDate tanggalPengembalian
               READ tanggalPengembalian
               WRITE setTanggalPengembalian
               NOTIFY tanggalPengembalianChanged)
    Q_PROPERTY(QList<PeminjamanBukuData *> bukuList READ bukuList WRITE setBukuList NOTIFY bukuListChanged FINAL)
    Q_PROPERTY(int dendaTerlambatPerBuku
               READ dendaTerlambatPerBuku
               WRITE setDendaTerlambatPerBuku
               NOTIFY dendaTerlambatPerBukuChanged)
    Q_PROPERTY(int totalDendaTerlambat
               READ totalDendaTerlambat
               NOTIFY totalDendaTerlambatChanged)
    Q_PROPERTY(int totalDenda
               READ totalDenda
               NOTIFY totalDendaChanged)
    QML_ELEMENT
public:
    explicit PeminjamanDendaCalculator(QObject *parent = nullptr);

    int dendaTerlambatPerBuku() const;
    void setDendaTerlambatPerBuku(int newDendaTenggatPerBuku);

    QDate tenggatPengembalian() const;
    void setTenggatPengembalian(const QDate &newTenggatPengembalian);

    QDate tanggalPengembalian() const;
    void setTanggalPengembalian(const QDate &newTanggalPengembalian);

    int totalDendaTerlambat() const;

    int totalDenda() const;

    QList<PeminjamanBukuData *> bukuList() const;
    void setBukuList(const QList<PeminjamanBukuData *> &newBukuList);

signals:
    void dendaTambahanBukuListChanged();
    void dendaTerlambatPerBukuChanged();
    void tenggatPengembalianChanged();
    void tanggalPengembalianChanged();
    void totalDendaTerlambatChanged();
    void totalDendaChanged();

    void bukuListChanged();

private slots:
    void calculateDenda();

private:
    QList<PeminjamanBukuData*> mBukuList;
    QDate mTenggatPengembalian;
    QDate mTanggalPengembalian;
    int mDendaTerlambatPerBuku;
    int mTotalDendaTerlambat;
    int mTotalDenda;
};

#endif // PEMINJAMANDENDACALCULATOR_H
