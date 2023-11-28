#include "peminjamanrepository.h"
#include "sqlhelper.h"
#include <QSqlQuery>
#include <QSqlError>

PeminjamanRepository::PeminjamanRepository(QObject *parent)
    : QObject{parent}
{

}

QList<PeminjamanData *> PeminjamanRepository::getList(PeminjamanData::StatusFilter statusFilter)
{
    QString queryString = "SELECT "
                          "   Detail_Peminjaman.kd_detail_peminjaman,"
                          "   Detail_Peminjaman.kd_member,"
                          "   Member.nama_depan_member,"
                          "   Member.nama_belakang_member,"
                          "   Detail_Peminjaman.tanggal_peminjaman,"
                          "   Detail_Peminjaman.lama_peminjaman,"
                          "   Detail_Peminjaman.tanggal_pengembalian,"
                          "   Detail_Peminjaman.denda_terlambat_perbuku "
                          "FROM Detail_Peminjaman "
                          "JOIN Member"
                          "   ON Member.kd_member = Detail_Peminjaman.kd_member";

    QStringList filterList;

    switch (statusFilter) {
    case PeminjamanData::MelewatiTenggatStatus:
        filterList.append("DATE("
                          " Detail_Peminjaman.tanggal_peminjaman, "
                          " Detail_Peminjaman.lama_peminjaman || ' days'"
                          ") < DATE('now')");
    case PeminjamanData::BelumDikembalikanStatus:
        filterList.append("Detail_Peminjaman.tanggal_pengembalian IS NULL");
        break;
    case PeminjamanData::SudahDikembalikanStatus:
        filterList.append("Detail_Peminjaman.tanggal_pengembalian IS NOT NULL");
        break;
    }

    if (filterList.length() > 0)
        queryString.append(QStringLiteral(" WHERE %1").arg(filterList.join(" AND ")));

    QSqlQuery query;

    if (!query.exec(queryString))
        qFatal() << "Cannot query Peminjaman " << query.lastError().text();

    QList<PeminjamanData*> result;

    while (query.next()) {
        result.append(new PeminjamanData(
            query.value(0).toInt(),
            query.value(1).toInt(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toDate(),
            query.value(5).toInt(),
            query.value(6).toDate(),
            query.value(7).toInt()
            ));
    }

    return result;
}

PeminjamanDetailData *PeminjamanRepository::get(int kode)
{
    QSqlQuery query;
    query.prepare("SELECT "
                  "   Detail_Peminjaman.kd_detail_peminjaman,"
                  "   Detail_Peminjaman.kd_member,"
                  "   Member.nama_depan_member,"
                  "   Member.nama_belakang_member,"
                  "   Detail_Peminjaman.tanggal_peminjaman,"
                  "   Detail_Peminjaman.lama_peminjaman,"
                  "   Detail_Peminjaman.tanggal_pengembalian,"
                  "   Detail_Peminjaman.denda_terlambat_perbuku,"
                  "   UserPeminjaman.id_user,"
                  "   UserPeminjaman.nama_depan_user,"
                  "   UserPeminjaman.nama_belakang_user,"
                  "   UserPengembalian.id_user,"
                  "   UserPengembalian.nama_depan_user,"
                  "   UserPengembalian.nama_belakang_user "
                  "FROM Detail_Peminjaman "
                  "JOIN Member"
                  "   ON Member.kd_member = Detail_Peminjaman.kd_member "
                  "JOIN User UserPeminjaman"
                  "   ON UserPeminjaman.id_user = Detail_Peminjaman.id_user_peminjaman "
                  "LEFT JOIN User UserPengembalian"
                  "   ON UserPengembalian.id_user = Detail_Peminjaman.id_user_pengembalian "
                  "WHERE Detail_Peminjaman.kd_detail_peminjaman = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot get data for peminjaman " << query.lastError().text();

    return query.next() ? new PeminjamanDetailData(
               query.value(0).toInt(),
               query.value(1).toInt(),
               query.value(2).toString(),
               query.value(3).toString(),
               query.value(4).toDate(),
               query.value(5).toInt(),
               query.value(6).toDate(),
               query.value(7).toInt(),
               query.value(8).toString(),
               query.value(9).toString(),
               query.value(10).toString(),
               query.value(11).toString(),
               query.value(12).toString(),
               query.value(13).toString()
               ) : new PeminjamanDetailData();
}

int PeminjamanRepository::add(int kodeMember, QString idUser, QDate tanggal, int lama)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Detail_Peminjaman ("
                  " kd_member,"
                  " id_user_peminjaman,"
                  " tanggal_peminjaman, "
                  " lama_peminjaman "
                  ") VALUES ("
                  " :member,"
                  " :user,"
                  " :tanggal,"
                  " :lama"
                  ")");
    query.bindValue(":user", idUser);
    query.bindValue(":member", kodeMember);
    query.bindValue(":tanggal", tanggal);
    query.bindValue(":lama", lama);

    if (!query.exec())
        qFatal() << "Cannot insert into Peminjaman " << query.lastError().text();

    emit dataChanged();

    return query.lastInsertId().toInt();
}

void PeminjamanRepository::update(int kode, int kodeMember, QDate tanggal, int lama)
{
    QSqlQuery query;
    query.prepare("UPDATE Detail_Peminjaman SET "
                  " kd_member = :member, "
                  " tanggal_peminjaman = :tanggal, "
                  " lama_peminjaman = :lama "
                  "WHERE "
                  " kd_detail_peminjaman = :kode"
                  );
    query.bindValue(":kode", kode);
    query.bindValue(":member", kodeMember);
    query.bindValue(":tanggal", tanggal);
    query.bindValue(":lama", lama);

    if (!query.exec())
        qFatal() << "Cannot update Peminjaman " << query.lastError().text();

    emit dataChanged();
}

void PeminjamanRepository::remove(int kode)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Detail_Peminjaman "
                  "WHERE kd_detail_peminjaman = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot remove peminjaman " << query.lastError().text();

    emit dataChanged();
}

void PeminjamanRepository::tandaiDikembalikan(int kode, QString idUser, QDate tanggal, int dendaTerlambatPerBukuHari)
{
    QSqlQuery query;
    query.prepare("UPDATE Detail_Peminjaman "
                  "SET "
                  " tanggal_pengembalian = :pengembalian,"
                  " id_user_pengembalian = :id_user,"
                  " denda_terlambat_perbuku = :denda_terlambat "
                  "WHERE kd_detail_peminjaman = :kode");
    query.bindValue(":kode", kode);
    query.bindValue(":pengembalian", tanggal);
    query.bindValue(":denda_terlambat", dendaTerlambatPerBukuHari);
    query.bindValue(":id_user", idUser);

    if (!query.exec())
        qFatal() << "Cannot add Pengembalian " << query.lastError().text();

    emit dataChanged();
}

void PeminjamanRepository::tandaiBelumDikembalikan(int kode)
{
    QSqlQuery query;
    query.prepare("UPDATE Detail_Peminjaman "
                  "SET "
                  " tanggal_pengembalian = NULL, "
                  " id_user_pengembalian = NULL,"
                  " denda_terlambat_perbuku = NULL "
                  "WHERE kd_detail_peminjaman = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot remove Pengembalian " << query.lastError().text();

    emit dataChanged();
}

QList<PeminjamanBukuData *> PeminjamanRepository::getBukuList(int kode)
{
    QSqlQuery query;
    query.prepare("SELECT"
                  " Peminjaman.kd_buku,"
                  " Buku.judul,"
                  " Peminjaman.denda_tambahan "
                  "FROM Peminjaman "
                  "LEFT JOIN Buku"
                  " ON Buku.kd_buku = Peminjaman.kd_buku "
                  "WHERE Peminjaman.kd_detail_peminjaman = :kode");

    query.bindValue(":kode", kode);
    if (!query.exec())
        qFatal() << "Cannot query PeminjamanBukuModel " << query.lastError().text();

    QList<PeminjamanBukuData*> result;

    while (query.next()) {
        result.append(new PeminjamanBukuData(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toInt()));
    }

    return result;
}

void PeminjamanRepository::addAllBuku(int kode, QList<PeminjamanBukuData *> bukuList)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.transaction())
        qFatal() << "Start transaction to addAll Peminjaman Buku" << db.lastError().text();

    internalUpdateAllBuku(kode, bukuList);

    if (!db.commit())
        qFatal() << "Cannot commit transaction for addAll Peminjaman Buku" << db.lastError().text();

    emit dataChanged();
}

void PeminjamanRepository::updateAllBuku(int kode, QList<PeminjamanBukuData *> bukuList)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction())
        qFatal() << "Cannot start transaction for updateALl Pemijaman buku" << db.lastError().text();

    internalUpdateAllBuku(kode, bukuList);

    QHash<QString, QVariant> queryBinds;
    QString queryString = "DELETE FROM"
                          " Peminjaman "
                          "WHERE "
                          " kd_detail_peminjaman = :peminjaman";

    if (bukuList.size() > 0) {
        QList<int> ignoredBuku(bukuList.size());

        for (int i = 0; i < bukuList.size(); i++) {
            ignoredBuku[i] = bukuList.at(i)->kodeBuku();
        }

        queryString.append(QStringLiteral(" AND kd_buku NOT IN (%1)")
                           .arg(SQLHelper::generateArrayBinds(
                                   ":ignored_buku",
                                   ignoredBuku,
                                   queryBinds
                                   )));
    }

    QSqlQuery query;
    query.prepare(queryString);

    query.bindValue(":peminjaman", kode);
    SQLHelper::applyBindMaps(query, queryBinds);

    if (!query.exec())
        qFatal() << "Deleting unused Peminjaman_buku fail " << query.lastError().text();

    if (!db.commit())
        qFatal() << "Cannot commit transaction for updateAll Peminjaman buku " << db.lastError().text();

    emit dataChanged();
}

void PeminjamanRepository::removeAllBuku(int kode)
{
    QSqlQuery query;
    query.prepare("DELETE FROM"
                  " Peminjaman "
                  "WHERE kd_detail_peminjaman = :kode");
    query.bindValue(":kode", kode);
    if (!query.exec())
        qFatal() << "Canot delete Peminjaman buku " << query.lastError().text();

    emit dataChanged();
}

void PeminjamanRepository::resetDendaBuku(int kode)
{
    QSqlQuery query;
    query.prepare("UPDATE Peminjaman "
                  "SET denda_tambahan = 0 "
                  "WHERE kd_detail_peminjaman = :kode");
    query.bindValue(":kode", kode);
    if (!query.exec())
        qFatal() << "Cannot reset denda for peminjaman" << query.lastError().text();

    emit dataChanged();
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

const QStringList PeminjamanRepository::bukuCandidateKey = {"kd_detail_peminjaman", "kd_buku"};

void PeminjamanRepository::internalUpdateAllBuku(int kode, QList<PeminjamanBukuData *> bukuList)
{
    QSqlDatabase db;
    QSqlQuery query(db);
    const int count = bukuList.count();
    for (int i = 0; i < count; i++){
        query.prepare(SQLHelper::createUpsertQuery(
            db,
            "Peminjaman("
            " kd_detail_peminjaman,"
            " kd_buku,"
            " denda_tambahan"
            ") VALUES ("
            " :peminjaman,"
            " :buku,"
            " :denda"
            ")",
            "denda_tambahan = :denda",
            bukuCandidateKey
            ));
        PeminjamanBukuData* buku = bukuList.at(i);
        query.bindValue(":peminjaman", kode);
        query.bindValue(":buku", buku->kodeBuku());
        query.bindValue(":denda", buku->denda());

        if (!query.exec())
            qFatal() << "Cannot upsert Peminjaman_buku " << query.lastError().text();
    }
}
