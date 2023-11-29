#ifndef BASEFIELDDATA_H
#define BASEFIELDDATA_H

#include <QObject>
#include <QQmlEngine>

class BaseFieldData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString errorText READ errorText NOTIFY errorTextChanged)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
public:
    explicit BaseFieldData(QObject *parent = nullptr);

    virtual QString errorText() const = 0;

    bool isValid() const;

signals:
    void errorTextChanged();
    void isValidChanged();
};

#endif // BASEFIELDDATA_H
