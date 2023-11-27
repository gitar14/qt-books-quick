#ifndef BUKUEDITVIEWMODEL_H
#define BUKUEDITVIEWMODEL_H

#include <QObject>
#include "textfielddata.h"
#include "combofielddata.h"
#include "repository/kategorirepository.h"
#include "repository/penerbitrepository.h"

class BukuEditViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isNew READ isNew NOTIFY isNewChanged)
    Q_PROPERTY(TextFieldData* judulField READ judulField CONSTANT)
    Q_PROPERTY(TextFieldData* penulisField READ penulisField CONSTANT)
    Q_PROPERTY(int jumlahHilang READ jumlahHilang WRITE jumlahHilang NOTIFY jumlahHilangChanged)
    Q_PROPERTY(int tahunTerbit READ tahunTerbit WRITE setTahunTerbit NOTIFY tahunTerbitChanged)
    Q_PROPERTY(ComboFieldData* kategoriField READ kategoriField CONSTANT)
    Q_PROPERTY(ComboFieldData* penerbitField READ penerbitField CONSTANT)
    Q_PROPERTY(QList<KategoriData *> kategoriList READ kategoriList NOTIFY kategoriListChanged FINAL)
    Q_PROPERTY(QList<PenerbitData*> penerbitList READ penerbitList NOTIFY penerbtitListChangedT)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
public:
    explicit BukuEditViewModel(QObject *parent = nullptr);

    Q_INVOKABLE void configure(int kode = -1);

    TextFieldData *judulField() const;

    TextFieldData *penulisField() const;

    int jumlahHilang() const;
    void jumlahHilang(int newJumlahHilang);

    int tahunTerbit() const;
    void setTahunTerbit(int newTahunTerbit);

    bool isNew() const;

    ComboFieldData *kategoriField() const;
    ComboFieldData *penerbitField() const;

    bool isValid() const;

    Q_INVOKABLE void submit();

    QList<KategoriData *> kategoriList() const;
    void setKategoriList(const QList<KategoriData *> &newKategoriList);

    QList<PenerbitData *> penerbitList() const;

signals:
    void jumlahHilangChanged();
    void tahunTerbitChanged();
    void isNewChanged();
    void isValidChanged();
    void kategoriListChanged();

    void penerbtitListChangedT();

private:
    int mKode;
    TextFieldData* mJudulField;
    TextFieldData* mPenulisField;
    int mJumlahHilang;
    int mTahunTerbit;

    ComboFieldData* mKategoriField;
    ComboFieldData* mPenerbitField;
    QList<KategoriData*> mKategoriList;
    QList<PenerbitData*> mPenerbitList;
};

#endif // BUKUEDITVIEWMODEL_H
