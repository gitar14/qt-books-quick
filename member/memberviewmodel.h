#ifndef MEMBERVIEWMODEL_H
#define MEMBERVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "memberpilihviewmodel.h"


class MemberViewModel : public MemberPilihViewModel
{
    Q_OBJECT
    Q_PROPERTY(MemberData *selectedData READ selectedData NOTIFY selectedDataChanged FINAL)
    QML_ELEMENT
public:
    explicit MemberViewModel(QObject *parent = nullptr);

    MemberData *selectedData() const;

    Q_INVOKABLE void removeSelectedItem();

signals:
    void selectedDataChanged();
private slots:
    void refreshSelectedData();

private:
    QScopedPointer<MemberData, QScopedPointerDeleteLater> mSelectedData;
};

#endif // MEMBERVIEWMODEL_H
