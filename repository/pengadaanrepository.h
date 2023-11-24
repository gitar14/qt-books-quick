#ifndef PENGADAANREPOSITORY_H
#define PENGADAANREPOSITORY_H

#include <QObject>

class PengadaanRepository : public QObject
{
    Q_OBJECT
public:
    explicit PengadaanRepository(QObject *parent = nullptr);

    int getJumlahPengadaanBuku(int kodeBuku);
signals:

};

#endif // PENGADAANREPOSITORY_H
