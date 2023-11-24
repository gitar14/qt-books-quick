#ifndef BUKUEDITVIEWMODEL_H
#define BUKUEDITVIEWMODEL_H

#include <QObject>
#include "textfielddata.h"
#include "combofielddata.h"
#include "repository/list/kategorimodel.h"
#include "repository/list/penerbitmodel.h"

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
    Q_PROPERTY(KategoriModel* kategoriListModel READ kategoriListModel CONSTANT)
    Q_PROPERTY(PenerbitModel* penerbitListModel READ penerbitListModel CONSTANT)
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

    KategoriModel *kategoriListModel() const;
    PenerbitModel *penerbitListModel() const;

    bool isNew() const;

    ComboFieldData *kategoriField() const;
    ComboFieldData *penerbitField() const;

    bool isValid() const;

    Q_INVOKABLE void submit();

signals:
    void jumlahHilangChanged();
    void tahunTerbitChanged();
    void isNewChanged();

    void isValidChanged();

private:
    int mKode;
    TextFieldData* mJudulField;
    TextFieldData* mPenulisField;
    int mJumlahHilang;
    int mTahunTerbit;

    ComboFieldData* mKategoriField;
    ComboFieldData* mPenerbitField;
    KategoriModel* mKategoriListModel;
    PenerbitModel* mPenerbitListModel;
    bool m_isValid;
};

#endif // BUKUEDITVIEWMODEL_H
