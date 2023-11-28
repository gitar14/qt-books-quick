#ifndef KATEGORI_H
#define KATEGORI_H

#include <QObject>

class KategoriData : public QObject {
    Q_OBJECT
    Q_PROPERTY(int kode READ kode CONSTANT FINAL)
    Q_PROPERTY(QString nama READ nama CONSTANT FINAL)
public:
    KategoriData(int kode = -1, const QString &nama = "");

    int kode() const;
    QString nama() const;

private:
    int mKode;
    QString mNama;
};

#endif // KATEGORI_H
