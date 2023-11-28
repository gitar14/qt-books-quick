#ifndef MEMBER_H
#define MEMBER_H

#include <QObject>
#include <QDate>

class MemberData : public QObject {
    Q_OBJECT
    Q_PROPERTY(int kode READ kode CONSTANT FINAL)
    Q_PROPERTY(QString namaDepan READ namaDepan CONSTANT FINAL)
    Q_PROPERTY(QString namaBelakang READ namaBelakang CONSTANT FINAL)
    Q_PROPERTY(QDate tanggalLahir READ tanggalLahir CONSTANT FINAL)
    Q_PROPERTY(QString nama READ nama CONSTANT FINAL)
    Q_PROPERTY(int umur READ umur CONSTANT FINAL)
public:
    MemberData(int kode = -1,
               const QString &namaDepan = "",
               const QString &namaBelakang = "",
               const QDate &tanggalLahir = QDate());

    int kode() const;
    QString namaDepan() const;
    QString namaBelakang() const;
    QDate tanggalLahir() const;

    QString nama() const;
    int umur() const;

private:
    int mKode;
    QString mNamaDepan;
    QString mNamaBelakang;
    QDate mTanggalLahir;
};


#endif // MEMBER_H
