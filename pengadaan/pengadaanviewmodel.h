#ifndef PENGADAANVIEWMODEL_H
#define PENGADAANVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/pengadaanrepository.h"

class PengadaanViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<PengadaanData*> list READ list NOTIFY listChanged)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged FINAL)
    Q_PROPERTY(PengadaanData *selectedData READ selectedData NOTIFY selectedDataChanged)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY hasSelectedItemChanged)
    Q_PROPERTY(QList<PengadaanBukuData *> selectedBukuList READ selectedBukuList NOTIFY selectedBukuListChanged)
    QML_ELEMENT
public:
    explicit PengadaanViewModel(QObject *parent = nullptr);
    ~PengadaanViewModel();

    QList<PengadaanData *> list() const;

    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);

    Q_INVOKABLE void setSelectedIndex(int newSelectedIndex);

    PengadaanData *selectedData() const;
    QList<PengadaanBukuData*> selectedBukuList() const;

    bool hasSelectedItem() const;

    Q_INVOKABLE void removeSelectedItem();

signals:
    void listChanged();
    void textQueryChanged();
    void selectedDataChanged();
    void selectedBukuListChanged();
    void hasSelectedItemChanged();

public slots:
    void refresh();

private:
    PengadaanRepository* mRepository;
    QList<PengadaanData*> mList;
    QString mTextQuery;
    int mSelectedIndex;
    PengadaanData *mSelectedData;
    QList<PengadaanBukuData*> mSelectedBukuList;

    void refreshSelectedItem();
};

#endif // PENGADAANVIEWMODEL_H
