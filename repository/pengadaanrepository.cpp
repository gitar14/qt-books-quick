#include "pengadaanrepository.h"
#include "sqlhelper.h"
#include <QSqlQuery>
#include <QSqlError>


PengadaanRepository::PengadaanRepository(QObject *parent)
    : QObject{parent}
{
    
}

QList<PengadaanData *> PengadaanRepository::getList(QString textQuery)
{
    QHash<QString,QVariant> binds;
    QString queryString = "SELECT "
                          "   kd_detail_pengadaan,"
                          "   sumber,"
                          "   tanggal_pengadaan "
                          "FROM Detail_Pengadaan";
    if(textQuery.length() > 0){
        queryString+= " WHERE sumber LIKE :textQuery";
        binds[":textQuery"]="%"+textQuery+"%";
    }

    QSqlQuery query;
    query.prepare(queryString);
    SQLHelper::applyBindMaps(query,binds);

    if (!query.exec())
        qFatal() << "Cannot query Pengadaan " << query.lastError().text() << query.lastQuery();

    QList<PengadaanData*> list;

    while (query.next()) {
        list.append(new PengadaanData(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toDate()
            ));
    }

    return list;
}

PengadaanDetailData *PengadaanRepository::get(int kode)
{
    QSqlQuery query;
    query.prepare("SELECT "
                  "   kd_detail_pengadaan,"
                  "   sumber,"
                  "   tanggal_pengadaan,"
                  "   User.id_user,"
                  "   User.nama_depan_user,"
                  "   User.nama_belakang_user "
                  "FROM Detail_Pengadaan "
                  "JOIN User ON User.id_user = Detail_Pengadaan.id_user "
                  "WHERE kd_detail_pengadaan = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot get pengadaan data " << query.lastError().text();

    return query.next() ? new PengadaanDetailData(
               query.value(0).toInt(),
               query.value(1).toString(),
               query.value(2).toDate(),
               query.value(3).toString(),
               query.value(4).toString(),
               query.value(5).toString()
               ) : new PengadaanDetailData();
}

int PengadaanRepository::add(QString sumber, QString idUser, QDate tanggalPengadaan)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Detail_Pengadaan("
                  " id_user,"
                  " sumber,"
                  " tanggal_pengadaan"
                  ") VALUES ("
                  " :user,"
                  " :sumber,"
                  " :tanggalPengadaan"
                  ")");
    query.bindValue(":user", idUser);
    query.bindValue(":sumber", sumber);
    query.bindValue(":tanggalPengadaan", tanggalPengadaan);

    if (!query.exec())
        qFatal() << "Cannot insert into Pengadaan " << query.lastError().text();

    emit dataChanged();

    return query.lastInsertId().toInt();
}

void PengadaanRepository::update(int kode, QString sumber, QDate tanggalPengadaan)
{
    QSqlQuery query;
    query.prepare("UPDATE Detail_Pengadaan SET"
                  " sumber = :sumber,"
                  " tanggal_pengadaan = :tanggal "
                  "WHERE "
                  " kd_detail_pengadaan = :kode"
                  );
    query.bindValue(":kode", kode);
    query.bindValue(":sumber", sumber);
    query.bindValue(":tanggal", tanggalPengadaan);

    if (!query.exec())
        qFatal() << "Cannot update Pengadaan " << query.lastError().text();

    emit dataChanged();
}

void PengadaanRepository::remove(int kode)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Detail_Pengadaan "
                  "WHERE kd_detail_pengadaan = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot remove pengadaan " << query.lastError().text();

    emit dataChanged();
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

QList<PengadaanBukuData *> PengadaanRepository::getBukuList(int kode)
{
    QSqlQuery query;
    query.prepare("SELECT "
                  " Pengadaan.kd_buku,"
                  " Pengadaan.jumlah_pengadaan_buku,"
                  " Buku.judul "
                  "FROM Pengadaan "
                  "LEFT JOIN Buku"
                  " ON Buku.kd_buku = Pengadaan.kd_buku "
                  "WHERE Pengadaan.kd_detail_pengadaan = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot get all pengadaan buku " << query.lastError().text();

    QList<PengadaanBukuData*> result;

    while (query.next()) {
        result.append(new PengadaanBukuData(
            query.value(0).toInt(),
            query.value(1).toInt(),
            query.value(2).toString()
            ));
    }

    return result;
}

void PengadaanRepository::updateAllBuku(int kode, QList<PengadaanBukuData *> list)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction())
        qFatal() << "Cannot start transaction for updateAll Pengadaan buku " << db.lastError().text();

    interalUpdateAllBuku(kode, list);

    QHash<QString, QVariant> queryBinds;
    QString queryString = "DELETE FROM"
                          "  Pengadaan "
                          "WHERE "
                          " kd_detail_pengadaan = :pengadaan";

    if (list.count() > 0) {
        QList<int> ignoredDelete(list.count());

        for (int i = 0; i < list.count(); i++) {
            ignoredDelete[i] = list.at(i)->kodeBuku();
        }

        queryString.append(QStringLiteral(" AND kd_buku NOT IN (%1)")
                           .arg(SQLHelper::generateArrayBinds(
                                ":ignored_kode",
                                ignoredDelete,
                                queryBinds
                                   )));
    }

    QSqlQuery query;
    query.prepare(queryString);

    query.bindValue(":pengadaan", kode);
    SQLHelper::applyBindMaps(query, queryBinds);

    if (!query.exec())
        qFatal() << "Deleting unused Pengadaan_buku fail " << query.lastError().text();

    if (!db.commit())
        qFatal() << "Cannot commit transaction for updateAll Pengadaan buku " << db.lastError().text();

    emit dataChanged();
}

void PengadaanRepository::addAllBuku(int kode, QList<PengadaanBukuData *> list)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.transaction())
        qFatal() << "Start transaction to addAll Pengadaan buku fail " << db.lastError().text();

    interalUpdateAllBuku(kode, list);

    if (!db.commit())
        qFatal() << "Cannot commit transaction for addAll Pengadaan buku " << db.lastError().text();

    emit dataChanged();
}

void PengadaanRepository::removeAllBuku(int kode)
{
    QSqlQuery query;
    query.prepare("DELETE FROM"
                  " Pengadaan "
                  "WHERE kd_detail_pengadaan = :kode");
    query.bindValue(":kode", kode);
    if (!query.exec())
        qFatal() << "Cannot delete Pengadaan buku " << query.lastError().text();

    emit dataChanged();
}

const QStringList PengadaanRepository::bukuCandidateKey = {"kd_detail_pengadaan", "kd_buku"};

void PengadaanRepository::interalUpdateAllBuku(int kode, QList<PengadaanBukuData *> list)
{
    QSqlDatabase db;
    QSqlQuery query(db);
    for (int i = 0; i < list.count(); i++) {
        const PengadaanBukuData* data = list.at(i);
        query.prepare(SQLHelper::createUpsertQuery(
            db,
            "Pengadaan("
            " kd_detail_pengadaan,"
            " kd_buku,"
            " jumlah_pengadaan_buku"
            ") VALUES ("
            " :pengadaan,"
            " :buku,"
            " :jumlah"
            ")",
            "jumlah_pengadaan_buku = :jumlah",
            bukuCandidateKey
            ));
        query.bindValue(":pengadaan", kode);
        query.bindValue(":buku", data->kodeBuku());
        query.bindValue(":jumlah", data->jumlah());
        if (!query.exec())
            qFatal() << "Cannot upsert Pengadaan_buku " << query.lastError().text() << query.lastQuery() ;
    }
}
