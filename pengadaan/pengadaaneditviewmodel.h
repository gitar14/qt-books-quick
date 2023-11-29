#ifndef PENGADAANEDITVIEWMODEL_H
#define PENGADAANEDITVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include "textfielddata.h"
#include "repository/pengadaanrepository.h"
#include "repository/bukurepository.h"

class PengadaanEditViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TextFieldData *sumberField READ sumberField CONSTANT FINAL)
    Q_PROPERTY(QDate tanggal READ tanggal WRITE setTanggal NOTIFY tanggalChanged FINAL)
    Q_PROPERTY(QList<PengadaanBukuData *> bukuList READ bukuList NOTIFY bukuListChanged FINAL)
    Q_PROPERTY(bool isBukuAvailable READ isBukuAvailable NOTIFY isBukuAvailableChanged FINAL)
    Q_PROPERTY(QList<int> kodeBukuList READ kodeBukuList NOTIFY kodeBukuListChanged FINAL)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
    QML_ELEMENT
public:
    explicit PengadaanEditViewModel(QObject *parent = nullptr);
    ~PengadaanEditViewModel();

    Q_INVOKABLE void configure(int kode = -1);

    TextFieldData *sumberField() const;
    QList<PengadaanBukuData *> bukuList() const;
    bool isBukuAvailable() const;

    Q_INVOKABLE void appendBuku(int kode);
    Q_INVOKABLE void removeBuku(int index);

    QList<int> kodeBukuList() const;

    QDate tanggal() const;
    void setTanggal(const QDate &newTanggal);

    bool isValid() const;

    Q_INVOKABLE void submit();

signals:
    void bukuListChanged();
    void isBukuAvailableChanged();
    void kodeBukuListChanged();

    void tanggalChanged();

    void isValidChanged();

private:
    PengadaanRepository* mRepository;
    int mKode;
    TextFieldData* mSumberField;
    QDate mTanggal;
    QList<PengadaanBukuData*> mBukuList;
    QList<int> mKodeBukuList;
    bool mIsBukuAvailable;

    void refreshBukuAvailable();
};

#endif // PENGADAANEDITVIEWMODEL_H
