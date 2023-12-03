#ifndef MEMBERVIEWMODEL_H
#define MEMBERVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "memberpilihviewmodel.h"


class MemberViewModel : public MemberPilihViewModel
{
    Q_OBJECT
    Q_PROPERTY(MemberDetailData *selectedData READ selectedData NOTIFY selectedDataChanged FINAL)
    QML_ELEMENT
public:
    explicit MemberViewModel(QObject *parent = nullptr);

    MemberDetailData *selectedData() const;

    Q_INVOKABLE void removeSelectedItem();

signals:
    void selectedDataChanged();
private slots:
    void refreshSelectedData();

private:
    QScopedPointer<MemberDetailData, QScopedPointerDeleteLater> mSelectedData;
};

#endif // MEMBERVIEWMODEL_H
