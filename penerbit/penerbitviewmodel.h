#ifndef PENERBITVIEWMODEL_H
#define PENERBITVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/penerbitrepository.h"

class PenerbitViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<PenerbitData*> list READ list NOTIFY listChanged FINAL)
    Q_PROPERTY(PenerbitData* selectedData READ selectedData NOTIFY selectedDataChanged)
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
    PenerbitData *selectedData() const;
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
    QList<PenerbitData*> mList;
    int mSelectedIndex;
    PenerbitData *mSelectedData = nullptr;
    QString mTextQuery;

    void refreshSelectedItem();
};

#endif // PENERBITVIEWMODEL_H
