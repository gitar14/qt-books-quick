#ifndef PEMINJAMANDENDAMODEL_H
#define PEMINJAMANDENDAMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QAbstractItemModel>

class PeminjamanDendaModel : public QObject
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
    Q_PROPERTY(int dendaTerlambatPerBuku
               READ dendaTerlambatPerBuku
               WRITE setDendaTerlambatPerBuku
               NOTIFY dendaTerlambatPerBukuChanged)
    Q_PROPERTY(QList<int> dendaTambahanBukuList
               READ dendaTambahanBukuList
               WRITE setDendaTambahanBukuList
               NOTIFY dendaTambahanBukuListChanged)
    Q_PROPERTY(int totalDendaTerlambat
               READ totalDendaTerlambat
               NOTIFY totalDendaTerlambatChanged)
    Q_PROPERTY(int totalDenda
               READ totalDenda
               NOTIFY totalDendaChanged)
    QML_ELEMENT
public:
    explicit PeminjamanDendaModel(QObject *parent = nullptr);

    QList<int> dendaTambahanBukuList() const;
    void setDendaTambahanBukuList(const QList<int> &newDendaTambahanBukuList);

    int dendaTerlambatPerBuku() const;
    void setDendaTerlambatPerBuku(int newDendaTenggatPerBuku);

    QDate tenggatPengembalian() const;
    void setTenggatPengembalian(const QDate &newTenggatPengembalian);

    QDate tanggalPengembalian() const;
    void setTanggalPengembalian(const QDate &newTanggalPengembalian);

    int totalDendaTerlambat() const;

    int totalDenda() const;

signals:
    void dendaTambahanBukuListChanged();
    void dendaTerlambatPerBukuChanged();
    void tenggatPengembalianChanged();
    void tanggalPengembalianChanged();
    void totalDendaTerlambatChanged();
    void totalDendaChanged();

private:
    QList<int> mDendaTambahanBukuList;
    int mDendaTerlambatPerBuku;
    QDate mTenggatPengembalian;
    QDate mTanggalPengembalian;
    int mTotalDendaTerlambat;

    void calculateDenda();
    int mTotalDenda;
};

#endif // PEMINJAMANDENDAMODEL_H
