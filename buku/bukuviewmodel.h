#ifndef BUKUVIEWMODEL_H
#define BUKUVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "bukupilihviewmodel.h"

class BukuViewModel : public BukuPilihViewModel
{
    Q_OBJECT
    Q_PROPERTY(const BukuData* selectedData READ selectedData NOTIFY selectedDataChanged)
    Q_PROPERTY(int selectedJumlahPengadaan READ selectedJumlahPengadaan NOTIFY selectedJumlahPengadaanChanged)
    Q_PROPERTY(int selectedJumlahDipinjam READ selectedJumlahDipinjam NOTIFY selectedJumlahDipinjamChanged)
    QML_ELEMENT
public:
    explicit BukuViewModel(QObject *parent = nullptr);

    BukuData *selectedData() const;
    int selectedJumlahPengadaan() const;
    int selectedJumlahDipinjam() const;

    Q_INVOKABLE void removeSelected();

signals:
    void selectedDataChanged();
    void selectedJumlahPengadaanChanged();
    void selectedJumlahDipinjamChanged();

protected:
    void refreshSelectedItem() override;
private:
    BukuData* mSelectedData;
    int mSelectedJumlahPengadaan;
    int mSelectedJumlahDipinjam;
};

#endif // BUKUVIEWMODEL_H
