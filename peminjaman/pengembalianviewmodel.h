#ifndef PENGEMBALIANVIEWMODEL_H
#define PENGEMBALIANVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/peminjamanrepository.h"
#include "peminjamandendacalculator.h"
#include "scopedobjectlist.h"

class PengembalianViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDate tanggalPengembalian READ tanggalPengembalian WRITE setTanggalPengembalian NOTIFY tanggalPengembalianChanged FINAL)
    Q_PROPERTY(QList<PeminjamanBukuData *> bukuList READ bukuList NOTIFY bukuListChanged FINAL)
    Q_PROPERTY(PeminjamanDendaCalculator *denda READ denda CONSTANT FINAL)
    QML_ELEMENT
public:
    explicit PengembalianViewModel(QObject *parent = nullptr);

    Q_INVOKABLE void configure(int kode);

    QDate tanggalPengembalian() const;
    void setTanggalPengembalian(const QDate &newTanggalPengembalian);
    QList<PeminjamanBukuData *> bukuList() const;
    PeminjamanDendaCalculator *denda() const;

    Q_INVOKABLE void submit();

signals:
    void tanggalPengembalianChanged();
    void bukuListChanged();

private:
    PeminjamanRepository* mRepository;
    int mKode;
    QDate mTanggalPengembalian;
    ScopedObjectList<PeminjamanBukuData> mBukuList;
    PeminjamanDendaCalculator* mDenda;
};

#endif // PENGEMBALIANVIEWMODEL_H
