#include "pengadaanrepository.h"
#include <QSqlQuery>
#include <QSqlError>

PengadaanRepository::PengadaanRepository(QObject *parent)
    : QObject{parent}
{

}

int PengadaanRepository::getJumlahPengadaanBuku(int kodeBuku)
{
    QSqlQuery query;
    query.prepare("SELECT "
                  "SUM(jumlah_pengadaan_buku) "
                  "FROM Pengadaan "
                  "WHERE kd_buku = :kode");
    query.bindValue(":kode", kodeBuku);

    if (!query.exec())
        qFatal() << "Cannot get jumlah pengadaan buku " << query.lastError().text();

    return query.next() ? query.value(0).toInt() : 0;
}
