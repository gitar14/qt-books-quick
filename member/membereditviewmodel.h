#ifndef MEMBEREDITVIEWMODEL_H
#define MEMBEREDITVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "textfielddata.h"
#include "repository/memberrepository.h"

class MemberEditViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TextFieldData *namaDepanField READ namaDepanField CONSTANT FINAL)
    Q_PROPERTY(TextFieldData *namaBelakangField READ namaBelakangField CONSTANT FINAL)
    Q_PROPERTY(QDate tanggalLahir READ tanggalLahir WRITE setTanggalLahir NOTIFY tanggalLahirChanged FINAL)
    Q_PROPERTY(bool isNew READ isNew NOTIFY isNewChanged)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
    QML_ELEMENT
public:
    explicit MemberEditViewModel(QObject *parent = nullptr);

    Q_INVOKABLE void configure(int kode = -1);

    TextFieldData *namaDepanField() const;
    TextFieldData *namaBelakangField() const;
    QDate tanggalLahir() const;
    void setTanggalLahir(const QDate &newTanggalLahir);
    bool isNew() const;
    bool isValid() const;

    Q_INVOKABLE void submit();

signals:
    void tanggalLahirChanged();
    void isNewChanged();
    void isValidChanged();

private:
    MemberRepository* mRepository;
    int mKode;
    TextFieldData* mNamaDepanField;
    TextFieldData* mNamaBelakangField;
    QDate mTanggalLahir;
};

#endif // MEMBEREDITVIEWMODEL_H
