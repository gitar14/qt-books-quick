#ifndef PENERBITEDITVIEWMODEL_H
#define PENERBITEDITVIEWMODEL_H

#include <QQmlEngine>
#include "textfielddata.h"

class PenerbitEditViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int kode READ kode WRITE setKode NOTIFY kodeChanged FINAL)
    Q_PROPERTY(bool isNew READ isNew NOTIFY kodeChanged)
    Q_PROPERTY(TextFieldData* namaField READ namaField CONSTANT)
    Q_PROPERTY(TextFieldData* alamatField READ alamatField CONSTANT)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
    QML_ELEMENT
public:
    explicit PenerbitEditViewModel(QObject *parent = nullptr);

    Q_INVOKABLE void configure(int kode = -1, QString nama = "", QString alamat = "");

    TextFieldData *namaField() const;
    TextFieldData *alamatField() const;

    int kode() const;
    void setKode(int newKode);

    bool isValid() const;
    bool isNew() const;

    Q_INVOKABLE void submit();

signals:
    void kodeChanged();
    void isValidChanged();

private:
    int mKode;
    TextFieldData* mNamaField;
    TextFieldData* mAlamatField;
};

#endif // PENERBITEDITVIEWMODEL_H
