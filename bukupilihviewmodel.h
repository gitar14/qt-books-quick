#ifndef BUKUPILIHVIEWMODEL_H
#define BUKUPILIHVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "kategorifiltermodel.h"
#include "penerbitfiltermodel.h"
#include "repository/bukurepository.h"

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
    Q_PROPERTY(KategoriFilterModel* kategoriFilterModel READ kategoriFilterModel CONSTANT)
    Q_PROPERTY(PenerbitFilterModel* penerbitFilterModel READ penerbitFilterModel CONSTANT)
    QML_ELEMENT
public:
    explicit BukuPilihViewModel(QObject *parent = nullptr);

    QList<BukuData *> list() const;

    KategoriFilterModel *kategoriFilterModel() const;
    PenerbitFilterModel *penerbitFilterModel() const;

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

protected:
    BukuRepository* mRepository;
    virtual void refreshSelectedItem();

private:
    QList<BukuData*> mList;
    QList<int> mIgnoredKode;
    int mSelectedIndex;
    int mSelectedKode;

    QString mTextQuery;
    int mKategoriFilter{-1};
    KategoriFilterModel* mKategoriFilterModel;
    int mPenerbitFilter{-1};
    PenerbitFilterModel* mPenerbitFilterModel;
};

#endif // BUKUPILIHVIEWMODEL_H
