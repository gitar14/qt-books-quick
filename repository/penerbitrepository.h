#ifndef PENERBITREPOSITORY_H
#define PENERBITREPOSITORY_H

#include <QObject>
class PenerbitData : public QObject {
    Q_OBJECT
    Q_PROPERTY(int kode READ kode CONSTANT FINAL)
    Q_PROPERTY(QString nama READ nama CONSTANT FINAL)
    Q_PROPERTY(QString alamat READ alamat CONSTANT FINAL)
public:
    PenerbitData(int kode = -1, const QString &nama = "", const QString &alamat = "");

    int kode() const;
    QString nama() const;
    QString alamat() const;

private:
    int mKode;
    QString mNama;
    QString mAlamat;
};

class PenerbitRepository : public QObject
{
    Q_OBJECT
public:
    explicit PenerbitRepository(QObject *parent = nullptr);

    QList<PenerbitData*> getAll(QString textQuery);
    PenerbitData* get(int kode);
    void add(QString nama, QString alamat);
    void edit(int kode, QString nama, QString alamat);
    void remove(int kode);

signals:
    void dataChanged();
};

#endif // PENERBITREPOSITORY_H
