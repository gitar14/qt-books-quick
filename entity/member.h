#ifndef MEMBER_H
#define MEMBER_H

#include <QObject>
#include <QDate>

class MemberData : public QObject {
    Q_OBJECT
    Q_PROPERTY(int kode READ kode CONSTANT FINAL)
    Q_PROPERTY(QString namaDepan READ namaDepan CONSTANT FINAL)
    Q_PROPERTY(QString namaBelakang READ namaBelakang CONSTANT FINAL)
    Q_PROPERTY(QString nama READ nama CONSTANT FINAL)
public:
    MemberData(int kode = -1,
               const QString &namaDepan = "",
               const QString &namaBelakang = "");

    int kode() const;
    QString namaDepan() const;
    QString namaBelakang() const;
    QString nama() const;

private:
    int mKode;
    QString mNamaDepan;
    QString mNamaBelakang;
};

class MemberDetailData : public MemberData {
    Q_OBJECT
    Q_PROPERTY(QDate tanggalLahir READ tanggalLahir CONSTANT FINAL)
    Q_PROPERTY(int umur READ umur CONSTANT FINAL)
public:
    MemberDetailData(int kode = -1,
                     const QString &namaDepan = "",
                     const QString &namaBelakang = "",
                     const QDate& tanggalLahir = QDate());

    QDate tanggalLahir() const;
    int umur() const;
private:
    QDate mTanggalLahir;

};

#endif // MEMBER_H
