#ifndef TEXTFIELDDATA_H
#define TEXTFIELDDATA_H

#include <QObject>
#include <QQmlEngine>
#include "basefielddata.h"

class TextFieldData : public BaseFieldData
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int maxLength READ maxLength WRITE setMaxLength NOTIFY maxLengthChanged)
    Q_PROPERTY(TextFieldData *referenceField READ referenceField WRITE setReferenceField NOTIFY referenceFieldChanged FINAL)
    QML_ELEMENT
public:
    explicit TextFieldData(QObject *parent = nullptr);

    QString value() const;
    void setValue(const QString &newValue);

    QString errorText() const;

    int maxLength() const;
    void setMaxLength(int newMaxLength);

    TextFieldData *referenceField() const;
    void setReferenceField(TextFieldData *newReferenceField);

signals:
    void valueChanged();
    void maxLengthChanged();
    void referenceFieldChanged();

private:
    QString mValue;
    int mMaxLength;
    int mAvailableLength;
    TextFieldData* mReferenceField = nullptr;
};

#endif // TEXTFIELDDATA_H
