#ifndef KATEGORIEDITVIEWMODEL_H
#define KATEGORIEDITVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "textfielddata.h"
#include "repository/kategorirepository.h"

class KategoriEditViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isNew READ isNew NOTIFY isNewChanged)
    Q_PROPERTY(TextFieldData* namaField READ namaField CONSTANT)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
    QML_ELEMENT
public:
    explicit KategoriEditViewModel(QObject *parent = nullptr);

    Q_INVOKABLE void configure(int kode = -1);

    Q_INVOKABLE void submit();

    TextFieldData *namaField() const;

    bool isValid() const;
    bool isNew() const;

signals:
    void isNewChanged();
    void isValidChanged();

private:
    KategoriRepository* mRepository;
    int mKode;
    TextFieldData* mNamaField;
};

#endif // KATEGORIEDITVIEWMODEL_H
