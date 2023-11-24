#ifndef PENERBITVIEWMODEL_H
#define PENERBITVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "repository/list/penerbitmodel.h"

class PenerbitViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PenerbitModel* listModel READ listModel CONSTANT)
    Q_PROPERTY(int selectedKode READ selectedKode NOTIFY selectedKodeChanged)
    Q_PROPERTY(bool hasSelectedItem READ hasSelectedItem NOTIFY selectedKodeChanged)
    Q_PROPERTY(QString selectedName READ selectedName NOTIFY selectedNameChanged)
    Q_PROPERTY(QString selectedAlamat READ selectedAlamat NOTIFY selectedAlamatChanged)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged)
    QML_ELEMENT
public:
    explicit PenerbitViewModel(QObject *parent = nullptr);

    PenerbitModel* listModel() const;

    int selectedKode() const;
    bool hasSelectedItem() const;
    QString selectedName() const;
    QString selectedAlamat() const;

    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);

    Q_INVOKABLE void setSelectedIndex(int index);
    Q_INVOKABLE void removeSelected();

signals:
    void selectedKodeChanged();
    void selectedNameChanged();
    void selectedAlamatChanged();
    void textQueryChanged();

public slots:
    void refreshSelectedItem();

private:
    PenerbitModel* mListModel;
    int mSelectedIndex;
    int mSelectedKode;
    QString mSelectedName;
    QString mSelectedAlamat;
    QString mTextQuery;
};

#endif // PENERBITVIEWMODEL_H
