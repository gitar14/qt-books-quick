#ifndef BUKUPILIHVIEWMODEL_H
#define BUKUPILIHVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/bukurepository.h"

class BukuPilihViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<BukuData *> list READ list NOTIFY listChanged FINAL)
    Q_PROPERTY(QList<int> ignoredKode READ ignoredKode WRITE setIgnoredKode NOTIFY ignoredKodeChanged FINAL)
    Q_PROPERTY(int selectedKode READ selectedKode NOTIFY selectedKodeChanged FINAL)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY hasSelectedItemChanged)
    QML_ELEMENT
public:
    explicit BukuPilihViewModel(QObject *parent = nullptr);

    QList<BukuData *> list() const;
    void setList(const QList<BukuData *> &newList);

    QList<int> ignoredKode() const;
    void setIgnoredKode(const QList<int> &newIgnoredKode);

    Q_INVOKABLE void setSelectedIndex(int index);

    bool hasSelectedItem() const;

    int selectedKode() const;

public slots:
    void refresh();

signals:
    void listChanged();
    void ignoredKodeChanged();
    void hasSelectedItemChanged();
    void selectedKodeChanged();

private:
    BukuRepository* mRepository;
    QList<BukuData*> mList;
    QList<int> mIgnoredKode;
    int mSelectedIndex;

    void refreshSelectedItem();
    int mSelectedKode;
};

#endif // BUKUPILIHVIEWMODEL_H
