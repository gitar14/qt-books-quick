#ifndef BUKUVIEWMODEL_H
#define BUKUVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "kategorifiltermodel.h"
#include "penerbitfiltermodel.h"
#include "repository/bukurepository.h"
#include "repository/list/bukulistmodel.h"

class BukuViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(KategoriFilterModel* kategoriFilterModel READ kategoriFilterModel CONSTANT)
    Q_PROPERTY(PenerbitFilterModel* penerbitFilterModel READ penerbitFilterModel CONSTANT)
    Q_PROPERTY(BukuListModel* listModel READ listModel CONSTANT)
    Q_PROPERTY(const BukuData* selectedData READ selectedData NOTIFY selectedDataChanged)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY selectedDataChanged)
    Q_PROPERTY(int selectedJumlahPengadaan READ selectedJumlahPengadaan NOTIFY selectedJumlahPengadaanChanged)
    Q_PROPERTY(int selectedJumlahDipinjam READ selectedJumlahDipinjam NOTIFY selectedJumlahDipinjamChanged)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged)
    Q_PROPERTY(int kategoriFilter READ kategoriFilter WRITE setKategoriFilter NOTIFY kategoriFilterChanged)
    Q_PROPERTY(int penerbitFilter READ penerbitFilter WRITE setPenerbitFilter NOTIFY penerbitFilterChanged)
    QML_ELEMENT
public:
    explicit BukuViewModel(QObject *parent = nullptr);

    BukuListModel *listModel() const;
    KategoriFilterModel *kategoriFilterModel() const;
    PenerbitFilterModel *penerbitFilterModel() const;

    Q_INVOKABLE void setSelectedIndex(int index);

    BukuData *selectedData() const;
    bool hasSelectedItem() const;
    int selectedJumlahPengadaan() const;
    int selectedJumlahDipinjam() const;

    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);

    int kategoriFilter() const;
    void setKategoriFilter(int newKategoriFilter);

    int penerbitFilter() const;
    void setPenerbitFilter(int newPenerbitFilter);

public slots:
    void refreshSelectedItem();

signals:
    void selectedDataChanged();
    void selectedJumlahPengadaanChanged();
    void selectedJumlahDipinjamChanged();
    void textQueryChanged();
    void kategoriFilterChanged();
    void penerbitFilterChanged();

private:
    KategoriFilterModel* mKategoriFilterModel;
    PenerbitFilterModel* mPenerbitFilterModel;
    BukuListModel* mListModel;

    int mSelectedIndex;
    BukuData* mSelectedData;
    int mSelectedJumlahPengadaan;
    int mSelectedJumlahDipinjam;

    QString mTextQuery;
    int mKategoriFilter;
    int mPenerbitFilter;
};

#endif // BUKUVIEWMODEL_H
