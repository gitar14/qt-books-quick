#ifndef MEMBERPILIHVIEWMODEL_H
#define MEMBERPILIHVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/memberrepository.h"
#include "scopedobjectlist.h"

class MemberPilihViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<MemberData *> list READ list NOTIFY listChanged FINAL)
    Q_PROPERTY(int selectedKode READ selectedKode WRITE setSelectedKode NOTIFY selectedKodeChanged FINAL)
    Q_PROPERTY(int selectedIndex READ selectedIndex WRITE setSelectedIndex NOTIFY selectedIndexChanged FINAL)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY hasSelectedItemChanged)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged FINAL)
    Q_PROPERTY(QList<int> ignoredKode READ ignoredKode WRITE setIgnoredKode NOTIFY ignoredKodeChanged FINAL)
    QML_ELEMENT
public:
    explicit MemberPilihViewModel(QObject *parent = nullptr);

    QList<MemberData *> list() const;
    int selectedKode() const;
    bool hasSelectedItem() const;
    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);

    void setSelectedIndex(int index);

    Q_INVOKABLE void init();

    QList<int> ignoredKode() const;
    void setIgnoredKode(const QList<int> &newIgnoredKode);

    void setSelectedKode(int newSelectedKode);

    int selectedIndex() const;

signals:
    void listChanged();
    void selectedKodeChanged();
    void hasSelectedItemChanged();
    void textQueryChanged();

    void ignoredKodeChanged();

    void selectedIndexChanged();

public slots:
    void refresh();

protected:
    MemberRepository* mRepository;

private:
    bool mIsInitialized = false;
    ScopedObjectList<MemberData> mList;
    int mSelectedIndex;
    int mSelectedKode;
    QString mTextQuery;
    QList<int> mIgnoredKode;

    void refreshSelectedItem();
};

#endif // MEMBERPILIHVIEWMODEL_H
