#ifndef PENERBITVIEWMODEL_H
#define PENERBITVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/penerbitrepository.h"
#include "scopedobjectlist.h"

class PenerbitViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<PenerbitData*> list READ list NOTIFY listChanged FINAL)
    Q_PROPERTY(PenerbitDetailData* selectedData READ selectedData NOTIFY selectedDataChanged)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY hasSelectedItemChanged)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged)
    QML_ELEMENT
public:
    explicit PenerbitViewModel(QObject *parent = nullptr);

    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);

    Q_INVOKABLE void setSelectedIndex(int index);
    Q_INVOKABLE void removeSelected();

    QList<PenerbitData *> list() const;
    PenerbitDetailData *selectedData() const;
    bool hasSelectedItem() const;

signals:
    void textQueryChanged();
    void listChanged();
    void selectedDataChanged();
    void hasSelectedItemChanged();

public slots:
    void refresh();

private:
    PenerbitRepository* mRepository;
    ScopedObjectList<PenerbitData> mList;
    int mSelectedIndex;
    QScopedPointer<PenerbitDetailData, QScopedPointerDeleteLater> mSelectedData;
    QString mTextQuery;

    void refreshSelectedItem();
};

#endif // PENERBITVIEWMODEL_H
