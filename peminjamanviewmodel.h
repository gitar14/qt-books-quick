#ifndef PEMINJAMANVIEWMODEL_H
#define PEMINJAMANVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/peminjamanrepository.h"
#include "peminjamandendacalculator.h"

class ProcessedPeminjamanData : public PeminjamanData {
    Q_OBJECT
    Q_PROPERTY(QString namaMember READ namaMember CONSTANT)
    Q_PROPERTY(QDate tenggatPengembalian READ tenggatPengembalian CONSTANT)
    Q_PROPERTY(bool sudahDikembalikan READ sudahDikembalikan CONSTANT)

public:
    ProcessedPeminjamanData(const PeminjamanData *rawData);
    QString namaMember() const;
    QDate tenggatPengembalian() const;
    bool sudahDikembalikan() const;
};

class PeminjamanViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<ProcessedPeminjamanData *> list READ list MEMBER mList NOTIFY listChanged FINAL)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged FINAL)
    Q_PROPERTY(StatusFilter statusFilter READ statusFilter WRITE setStatusFilter NOTIFY statusFilterChanged FINAL)
    Q_PROPERTY(ProcessedPeminjamanData *selectedData READ selectedData NOTIFY selectedDataChanged FINAL)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY hasSelectedItemChanged)
    Q_PROPERTY(QList<PeminjamanBukuData *> selectedBukuList READ selectedBukuList NOTIFY selectedBukuListChanged FINAL)
    Q_PROPERTY(PeminjamanDendaCalculator *selectedDenda READ selectedDenda CONSTANT FINAL)
    QML_ELEMENT
public:
    explicit PeminjamanViewModel(QObject *parent = nullptr);

    enum StatusFilter {
        SemuaStatus = 0,
        BelumDikembalikanStatus,
        MelewatiTenggatStatus,
        SudahDikembalikanStatus
    };
    Q_ENUM(StatusFilter)

    QList<ProcessedPeminjamanData *> list() const;
    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);
    StatusFilter statusFilter() const;
    void setStatusFilter(StatusFilter newStatusFilter);
    ProcessedPeminjamanData *selectedData() const;
    bool hasSelectedItem() const;

    Q_INVOKABLE void setSelectedIndex(int index);

    QList<PeminjamanBukuData *> selectedBukuList() const;

    PeminjamanDendaCalculator *selectedDenda() const;

    Q_INVOKABLE void tandaiBelumDikembalikanSelected();

public slots:
    void refresh();

signals:
    void listChanged();
    void textQueryChanged();
    void statusFilterChanged();
    void selectedDataChanged();
    void hasSelectedItemChanged();
    void selectedBukuListChanged();

private:
    PeminjamanRepository *mRepository;
    QList<ProcessedPeminjamanData*> mList;
    QString mTextQuery;
    StatusFilter mStatusFilter;
    int mSelectedIndex;
    ProcessedPeminjamanData* mSelectedData;
    QList<PeminjamanBukuData*> mSelectedBukuList;
    PeminjamanDendaCalculator* mSelectedDenda;

    void refreshSelectedItem();
};

#endif // PEMINJAMANVIEWMODEL_H
