#ifndef BASEFIELDDATA_H
#define BASEFIELDDATA_H

#include <QObject>
#include <QQmlEngine>

class BaseFieldData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString errorText READ errorText NOTIFY errorTextChanged)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
public:
    explicit BaseFieldData(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &newName);

    virtual QString errorText() const = 0;

    bool isValid() const;

signals:
    void nameChanged();
    void errorTextChanged();
    void isValidChanged();

private:
    QString mName;
    bool m_isValid;
};

#endif // BASEFIELDDATA_H
