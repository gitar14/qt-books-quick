#ifndef BUKUVIEWMODEL_H
#define BUKUVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "bukupilihviewmodel.h"

class BukuJumlahViewData : public QObject {
    Q_OBJECT
    Q_PROPERTY(int pengadaan READ pengadaan CONSTANT FINAL)
    Q_PROPERTY(int tidakHilang READ tidakHilang CONSTANT FINAL)
    Q_PROPERTY(int dipinjam READ dipinjam CONSTANT FINAL)
    Q_PROPERTY(int tersedia READ tersedia CONSTANT FINAL)
public:
    explicit BukuJumlahViewData(int jumlahPengadaan = 0, int jumlahHilang = 0, int jumlahDipinjam = 0);
    int pengadaan() const;
    int tidakHilang() const;
    int dipinjam() const;
    int tersedia() const;

private:
    int mPengadaan;
    int mTidakHilang;
    int mDipinjam;
    int mTersedia;
};

class BukuViewModel : public BukuPilihViewModel
{
    Q_OBJECT
    Q_PROPERTY(const BukuDetailData* selectedData READ selectedData NOTIFY selectedDataChanged)
    Q_PROPERTY(BukuJumlahViewData* selectedDataJumlah READ selectedDataJumlah NOTIFY selectedDataJumlahChanged FINAL)
    QML_ELEMENT
public:
    explicit BukuViewModel(QObject *parent = nullptr);

    BukuDetailData *selectedData() const;

    Q_INVOKABLE void removeSelected();
    BukuJumlahViewData *selectedDataJumlah() const;

signals:
    void selectedDataChanged();
    void selectedDataJumlahChanged();

private slots:
    void refreshSelectedData();

private:
    BukuDetailData* mSelectedData;
    QScopedPointer<BukuJumlahViewData, QScopedPointerDeleteLater> mSelectedDataJumlah;
};

#endif // BUKUVIEWMODEL_H
