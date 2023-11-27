#ifndef MEMBERPILIHVIEWMODEL_H
#define MEMBERPILIHVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/memberrepository.h"

class MemberPilihViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<MemberData *> list READ list NOTIFY listChanged FINAL)
    Q_PROPERTY(int selectedKode READ selectedKode NOTIFY selectedKodeChanged FINAL)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY hasSelectedItemChanged)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged FINAL)
    QML_ELEMENT
public:
    explicit MemberPilihViewModel(QObject *parent = nullptr);

    QList<MemberData *> list() const;
    int selectedKode() const;
    bool hasSelectedItem() const;
    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);

    Q_INVOKABLE void setSelectedIndex(int index);

signals:
    void listChanged();
    void selectedKodeChanged();
    void hasSelectedItemChanged();
    void textQueryChanged();

private slots:
    void refresh();

protected:
    MemberRepository* mRepository;

private:
    QList<MemberData*> mList;
    int mSelectedIndex;
    int mSelectedKode;
    QString mTextQuery;

    void refreshSelectedItem();
};

#endif // MEMBERPILIHVIEWMODEL_H
