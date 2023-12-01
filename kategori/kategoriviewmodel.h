#ifndef KATEGORIVIEWMODEL_H
#define KATEGORIVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/kategorirepository.h"
#include "scopedobjectlist.h"

class KategoriViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<KategoriData *> list READ list NOTIFY listChanged FINAL)
    Q_PROPERTY(KategoriData* selectedData READ selectedData NOTIFY selectedDataChanged)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY hasSelectedItemChanged)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged)
    QML_ELEMENT
public:
    explicit KategoriViewModel(QObject *parent = nullptr);

    Q_INVOKABLE void setSelectedIndex(int index);
    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);

    Q_INVOKABLE void removeSelected();

    bool hasSelectedItem() const;

    QList<KategoriData *> list() const;
    void setList(const QList<KategoriData *> &newList);

    KategoriData *selectedData() const;

public slots:
    void refresh();

signals:
    void textQueryChanged();
    void listChanged();
    void hasSelectedItemChanged();
    void selectedDataChanged();

private:
    KategoriRepository *mRepository;
    ScopedObjectList<KategoriData> mList;
    int mSelectedIndex;
    QString mTextQuery;
    QScopedPointer<KategoriData, QScopedPointerDeleteLater> mSelectedData;

    void refreshSelectedItem();
};

#endif // KATEGORIVIEWMODEL_H
