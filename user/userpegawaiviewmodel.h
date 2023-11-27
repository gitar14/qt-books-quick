#ifndef USERPEGAWAIVIEWMODEL_H
#define USERPEGAWAIVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/userrepository.h"

class UserPegawaiViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<UserData *> list READ list NOTIFY listChanged FINAL)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged FINAL)
    Q_PROPERTY(UserData *selectedData READ selectedData NOTIFY selectedDataChanged FINAL)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY hasSelectedItemChanged)
    QML_ELEMENT
public:
    explicit UserPegawaiViewModel(QObject *parent = nullptr);

    QList<UserData *> list() const;
    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);

    Q_INVOKABLE void setSelectedIndex(int newSelectedIndex);

    UserData *selectedData() const;

    bool hasSelectedItem() const;

signals:
    void listChanged();
    void textQueryChanged();
    void selectedDataChanged();

    void hasSelectedItemChanged();

private slots:
    void refresh();

private:
    UserRepository* mRepository;
    QList<UserData*> mList;
    QString mTextQuery;
    int mSelectedIndex;
    UserData* mSelectedData;

    void refreshSelectedItem();
};

#endif // USERPEGAWAIVIEWMODEL_H
