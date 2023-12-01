#ifndef PEMINJAMANVIEWMODEL_H
#define PEMINJAMANVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/peminjamanrepository.h"
#include "peminjamandendacalculator.h"
#include "scopedobjectlist.h"

class PeminjamanViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<PeminjamanData *> list READ list NOTIFY listChanged FINAL)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged FINAL)
    Q_PROPERTY(PeminjamanData::StatusFilter statusFilter READ statusFilter WRITE setStatusFilter NOTIFY statusFilterChanged FINAL)
    Q_PROPERTY(PeminjamanDetailData *selectedData READ selectedData NOTIFY selectedDataChanged FINAL)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY hasSelectedItemChanged)
    Q_PROPERTY(QList<PeminjamanBukuData *> selectedBukuList READ selectedBukuList NOTIFY selectedBukuListChanged FINAL)
    Q_PROPERTY(PeminjamanDendaCalculator *selectedDenda READ selectedDenda CONSTANT FINAL)
    QML_ELEMENT
public:
    explicit PeminjamanViewModel(QObject *parent = nullptr);

    QList<PeminjamanData *> list() const;
    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);
    PeminjamanData::StatusFilter statusFilter() const;
    void setStatusFilter(PeminjamanData::StatusFilter newStatusFilter);
    PeminjamanDetailData *selectedData() const;
    bool hasSelectedItem() const;

    Q_INVOKABLE void setSelectedIndex(int index);

    QList<PeminjamanBukuData *> selectedBukuList() const;

    PeminjamanDendaCalculator *selectedDenda() const;

    Q_INVOKABLE void tandaiBelumDikembalikanSelected();

    Q_INVOKABLE void removeSelectedItem();

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
    ScopedObjectList<PeminjamanData> mList;
    QString mTextQuery;
    PeminjamanData::StatusFilter mStatusFilter = PeminjamanData::BelumDikembalikanStatus;
    int mSelectedIndex;
    QScopedPointer<PeminjamanDetailData> mSelectedData;
    ScopedObjectList<PeminjamanBukuData> mSelectedBukuList;
    PeminjamanDendaCalculator* mSelectedDenda;

    void refreshSelectedItem();
};

#endif // PEMINJAMANVIEWMODEL_H
