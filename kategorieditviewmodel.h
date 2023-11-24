#ifndef KATEGORIEDITVIEWMODEL_H
#define KATEGORIEDITVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "textfielddata.h"

class KategoriEditViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int kode READ kode WRITE setKode NOTIFY kodeChanged)
    Q_PROPERTY(bool isNew READ isNew NOTIFY kodeChanged)
    Q_PROPERTY(TextFieldData* namaField READ namaField CONSTANT)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
    QML_ELEMENT
public:
    explicit KategoriEditViewModel(QObject *parent = nullptr);

    Q_INVOKABLE void configure(int kode = -1, QString nama = "");

    int kode() const;
    void setKode(int newKode);

    Q_INVOKABLE void submit();

    TextFieldData *namaField() const;

    bool isValid() const;
    bool isNew() const;

signals:
    void kodeChanged();
    void isValidChanged();

private:
    int mKode;
    TextFieldData* mNamaField;
};

#endif // KATEGORIEDITVIEWMODEL_H
