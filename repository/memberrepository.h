#ifndef MEMBERREPOSITORY_H
#define MEMBERREPOSITORY_H

#include <QObject>
#include <QDate>

class MemberData : public QObject {
    Q_OBJECT
public:
    MemberData(int kode = -1,
               const QString &namaDepan = "",
               const QString &namaBelakang = "",
               const QDate &tanggalLahir = QDate());

    int kode() const;
    QString namaDepan() const;
    QString namaBelakang() const;
    QDate tanggalLahir() const;

private:
    int mKode;
    QString mNamaDepan;
    QString mNamaBelakang;
    QDate mTanggalLahir;
    Q_PROPERTY(int kode READ kode CONSTANT FINAL)
    Q_PROPERTY(QString namaDepan READ namaDepan CONSTANT FINAL)
    Q_PROPERTY(QString namaBelakang READ namaBelakang CONSTANT FINAL)
    Q_PROPERTY(QDate tanggalLahir READ tanggalLahir CONSTANT FINAL)
};

class MemberRepository : public QObject
{
    Q_OBJECT
public:
    explicit MemberRepository(QObject *parent = nullptr);

    QList<MemberData*> getAll(QString textQuery);
    MemberData* get(int kode);
    void add(QString namaDepan, QString namaBelakang, QDate tanggalLahir);
    void edit(int kode, QString namaDepan, QString namaBelakang, QDate tanggalLahir);
    void remove(int kode);

signals:
    void dataChanged();
};

#endif // MEMBERREPOSITORY_H
