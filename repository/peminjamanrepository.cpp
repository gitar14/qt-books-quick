#include "peminjamanrepository.h"
#include <QSqlQuery>
#include <QSqlError>

PeminjamanRepository::PeminjamanRepository(QObject *parent)
    : QObject{parent}
{

}

int PeminjamanRepository::getJumlahBukuDipinjam(int kodeBuku)
{
    QSqlQuery query;
    query.prepare("SELECT "
                  "COUNT(Peminjaman.kd_peminjaman) "
                  "FROM Peminjaman "
                  "INNER JOIN Detail_Peminjaman "
                  " ON Detail_Peminjaman.kd_detail_peminjaman = Peminjaman.kd_detail_peminjaman "
                  "WHERE Peminjaman.kd_buku = :kode AND Detail_Peminjaman.tanggal_pengembalian IS NULL");
    query.bindValue(":kode", kodeBuku);

    if (!query.exec())
        qFatal() << "Cannot get jumlah buku dipinjam " << query.lastError().text() << query.lastError().nativeErrorCode();

    return query.next() ? query.value(0).toInt() : 0;
}
