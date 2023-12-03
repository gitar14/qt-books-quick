#ifndef PENERBIT_H
#define PENERBIT_H

#include <QObject>

class PenerbitData : public QObject {
    Q_OBJECT
    Q_PROPERTY(int kode READ kode CONSTANT FINAL)
    Q_PROPERTY(QString nama READ nama CONSTANT FINAL)
public:
    PenerbitData(int kode = -1, const QString &nama = "");

    int kode() const;
    QString nama() const;

private:
    int mKode;
    QString mNama;
};

class PenerbitDetailData : public PenerbitData {
    Q_OBJECT
    Q_PROPERTY(QString alamat READ alamat CONSTANT FINAL)
public:
    PenerbitDetailData(int kode = -1, const QString &nama = "", const QString &alamat = "");

    QString alamat() const;

private:
    QString mAlamat;
};

#endif // PENERBIT_H
