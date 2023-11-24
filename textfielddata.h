#ifndef TEXTFIELDDATA_H
#define TEXTFIELDDATA_H

#include <QObject>

class TextFieldData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString errorText READ errorText NOTIFY errorTextChanged)
    Q_PROPERTY(int maxLength READ maxLength WRITE setMaxLength NOTIFY maxLengthChanged)
    Q_PROPERTY(int availableLength READ availableLength NOTIFY availableLengthChanged)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
public:
    explicit TextFieldData(QObject *parent = nullptr);

    QString value() const;
    void setValue(const QString &newValue);

    QString errorText() const;
    bool isValid() const;

    int maxLength() const;
    void setMaxLength(int newMaxLength);

    int availableLength() const;

    QString name() const;
    void setName(const QString &newName);

signals:
    void valueChanged();
    void maxLengthChanged();
    void errorTextChanged();
    void availableLengthChanged();
    void nameChanged();

    void isValidChanged();

private:
    QString mValue;
    int mMaxLength;
    int mAvailableLength;
    QString mName;
};

#endif // TEXTFIELDDATA_H
