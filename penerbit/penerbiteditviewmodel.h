#ifndef PENERBITEDITVIEWMODEL_H
#define PENERBITEDITVIEWMODEL_H

#include <QQmlEngine>
#include "textfielddata.h"
#include "repository/penerbitrepository.h"

class PenerbitEditViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isNew READ isNew NOTIFY isNewChanged)
    Q_PROPERTY(TextFieldData* namaField READ namaField CONSTANT)
    Q_PROPERTY(TextFieldData* alamatField READ alamatField CONSTANT)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
    QML_ELEMENT
public:
    explicit PenerbitEditViewModel(QObject *parent = nullptr);

    Q_INVOKABLE void configure(int kode = -1);

    TextFieldData *namaField() const;
    TextFieldData *alamatField() const;

    bool isValid() const;
    bool isNew() const;

    Q_INVOKABLE void submit();

signals:
    void isNewChanged();
    void isValidChanged();

private:
    PenerbitRepository* mRepository;
    int mKode;
    TextFieldData* mNamaField;
    TextFieldData* mAlamatField;
};

#endif // PENERBITEDITVIEWMODEL_H
