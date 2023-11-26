#ifndef MEMBERVIEWMODEL_H
#define MEMBERVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/memberrepository.h"

class MemberViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<MemberData *> list READ list NOTIFY listChanged FINAL)
    Q_PROPERTY(MemberData *selectedData READ selectedData NOTIFY selectedDataChanged FINAL)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY hasSelectedItemChanged)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged FINAL)
    QML_ELEMENT
public:
    explicit MemberViewModel(QObject *parent = nullptr);

    QList<MemberData *> list() const;
    MemberData *selectedData() const;
    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);
    bool hasSelectedItem() const;

    Q_INVOKABLE void setSelectedIndex(int index);
    Q_INVOKABLE void removeSelectedItem();

signals:
    void listChanged();
    void selectedDataChanged();
    void textQueryChanged();

    void hasSelectedItemChanged();

private slots:
    void refresh();

private:
    MemberRepository* mRepository;
    QList<MemberData*> mList;
    int mSelectedIndex;
    MemberData* mSelectedData;
    QString mTextQuery;

    void refreshSelectedItem();
};

#endif // MEMBERVIEWMODEL_H
