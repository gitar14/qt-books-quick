#ifndef BUKUPILIHVIEWMODEL_H
#define BUKUPILIHVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/kategorirepository.h"
#include "repository/penerbitrepository.h"
#include "repository/bukurepository.h"
#include "safeobjectlist.h"

class BukuPilihViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<BukuData *> list READ list NOTIFY listChanged FINAL)
    Q_PROPERTY(QList<int> ignoredKode READ ignoredKode WRITE setIgnoredKode NOTIFY ignoredKodeChanged FINAL)
    Q_PROPERTY(int selectedKode READ selectedKode NOTIFY selectedKodeChanged FINAL)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY hasSelectedItemChanged)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged)
    Q_PROPERTY(int kategoriFilter READ kategoriFilter WRITE setKategoriFilter NOTIFY kategoriFilterChanged)
    Q_PROPERTY(int penerbitFilter READ penerbitFilter WRITE setPenerbitFilter NOTIFY penerbitFilterChanged)
    Q_PROPERTY(QList<KategoriData *> kategoriFilterList READ kategoriFilterList NOTIFY kategoriFilterListChanged FINAL)
    Q_PROPERTY(QList<PenerbitData *> penerbitFilterList READ penerbitFilterModel NOTIFY penerbitFilerListChanged)
    QML_ELEMENT
public:
    explicit BukuPilihViewModel(QObject *parent = nullptr);

    QList<BukuData *> list() const;

    QList<int> ignoredKode() const;
    void setIgnoredKode(const QList<int> &newIgnoredKode);

    Q_INVOKABLE void setSelectedIndex(int index);

    bool hasSelectedItem() const;

    int selectedKode() const;

    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);

    int kategoriFilter() const;
    void setKategoriFilter(int newKategoriFilter);

    int penerbitFilter() const;
    void setPenerbitFilter(int newPenerbitFilter);

    QList<KategoriData *> kategoriFilterList() const;
    QList<PenerbitData *> penerbitFilterModel() const;

    Q_INVOKABLE void init();

public slots:
    void refresh();

signals:
    void listChanged();
    void ignoredKodeChanged();
    void hasSelectedItemChanged();
    void selectedKodeChanged();
    void textQueryChanged();
    void kategoriFilterChanged();
    void penerbitFilterChanged();

    void kategoriFilterListChanged();

    void penerbitFilerListChanged();

protected:
    BukuRepository* mRepository;

private:
    SafeObjectList<BukuData> mList;
    QList<int> mIgnoredKode;
    int mSelectedIndex;
    int mSelectedKode;
    bool mIsIntialized = false;

    QString mTextQuery;
    int mKategoriFilter{-1};
    SafeObjectList<KategoriData> mKategoriFilterList;
    int mPenerbitFilter{-1};
    SafeObjectList<PenerbitData> mPenerbitFilterList;

    void refreshSelectedItem();
};

#endif // BUKUPILIHVIEWMODEL_H
