#ifndef COMBOFIELDDATA_H
#define COMBOFIELDDATA_H

#include "basefielddata.h"
#include <QObject>
#include <QQmlEngine>

class ComboFieldData : public BaseFieldData
{
    Q_OBJECT
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)
    QML_ELEMENT
public:
    explicit ComboFieldData(QObject *parent = nullptr);

    QString errorText() const;

    int index() const;
    void setIndex(int newIndex);

signals:
    void indexChanged();
private:
    int mIndex;
};

#endif // COMBOFIELDDATA_H
