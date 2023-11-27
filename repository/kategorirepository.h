#ifndef KATEGORIREPOSITORY_H
#define KATEGORIREPOSITORY_H

#include <Qt>
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

class KategoriRepository : public QObject
{
    Q_OBJECT
public:
    explicit KategoriRepository(QObject *parent = nullptr);

    QList<KategoriData*> getAll(QString textQuery);
    KategoriData* get(int kode);
    void addNew(QString jenis);
    void edit(int kode, QString jenis);
    void remove(int kode);
signals:
    void dataChanged();
};

#endif // KATEGORIREPOSITORY_H
