#ifndef KATEGORIVIEWMODEL_H
#define KATEGORIVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/list/kategorimodel.h"

class KategoriViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(KategoriModel* listModel READ listModel CONSTANT)
    Q_PROPERTY(int selectedKode READ selectedKode NOTIFY selectedKodeChanged)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY selectedKodeChanged)
    Q_PROPERTY(QString selectedName READ selectedName NOTIFY selectedNameChanged)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged)
    QML_ELEMENT
public:
    explicit KategoriViewModel(QObject *parent = nullptr);

    KategoriModel *listModel() const;

    Q_INVOKABLE void setSelectedIndex(int index);

    int selectedKode() const;
    QString selectedName() const;

    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);

    Q_INVOKABLE void removeSelected();

    bool hasSelectedItem() const;

public slots:
    void refreshSelectedItem();

signals:
    void selectedKodeChanged();
    void selectedNameChanged();
    void textQueryChanged();

private:
    KategoriModel *mListModel;
    int mSelectedIndex;
    int mSelectedKode;
    QString mSelectedName;
    QString mTextQuery;
};

#endif // KATEGORIVIEWMODEL_H
