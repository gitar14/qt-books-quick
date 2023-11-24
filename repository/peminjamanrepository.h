#ifndef PEMINJAMANREPOSITORY_H
#define PEMINJAMANREPOSITORY_H

#include <QObject>

class PeminjamanRepository : public QObject
{
    Q_OBJECT
public:
    explicit PeminjamanRepository(QObject *parent = nullptr);

    int getJumlahBukuDipinjam(int kodeBuku);
signals:

};

#endif // PEMINJAMANREPOSITORY_H
