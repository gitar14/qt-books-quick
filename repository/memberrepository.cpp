#include "memberrepository.h"
#include "sqlhelper.h"
#include <QSqlQuery>
#include <QSqlError>

MemberRepository::MemberRepository(QObject *parent)
    : QObject{parent}
{

}

QList<MemberData *> MemberRepository::getAll(QList<int> ignoredKode, QString textQuery)
{
    QHash<QString,QVariant>binds;
    QString queryString = "SELECT "
                          "   kd_member,"
                          "   nama_depan_member,"
                          "   nama_belakang_member "
                          "FROM Member";
    QStringList filterList;

    if (textQuery.length() > 0) {
        filterList.append("(nama_depan_member || ' ' || nama_belakang_member) LIKE :textQuery");
        binds[":textQuery"]="%"+ textQuery +"%";
    }

    if (ignoredKode.length() > 0) {
        filterList.append(QStringLiteral("kd_member NOT IN (%1)").arg(
            SQLHelper::generateArrayBinds(":ignored_kode_", ignoredKode, binds)
            ));
    }

    if (filterList.length() > 0) {
        queryString += " WHERE " + filterList.join(" AND ");
    }

    QSqlQuery query;
    query.prepare(queryString);
    SQLHelper::applyBindMaps(query,binds);

    if (!query.exec())
        qFatal() << "Cannot select from Member" << query.lastError().text();

    QList<MemberData*> result;

    while (query.next()) {
        result.push_back(new MemberData(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString()
            ));
    }

    return result;
}

MemberDetailData *MemberRepository::get(int kode)
{
    QSqlQuery query;
    query.prepare("SELECT "
                  "   kd_member,"
                  "   nama_depan_member,"
                  "   nama_belakang_member,"
                  "   tanggal_lahir "
                  "FROM Member "
                  "WHERE kd_member = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot get Member data " << query.lastError().text();

    return query.next() ? new MemberDetailData(
        query.value(0).toInt(),
        query.value(1).toString(),
        query.value(2).toString(),
        query.value(3).toDate()
               ) : new MemberDetailData();
}

void MemberRepository::add(QString namaDepan, QString namaBelakang, QDate tanggalLahir)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Member("
                  " nama_depan_member,"
                  " nama_belakang_member,"
                  " tanggal_lahir"
                  ") VALUES ("
                  " :namaDepan,"
                  " :namaBelakang,"
                  " :tanggalLahir"
                  ")");

    query.bindValue(":namaDepan", namaDepan);
    query.bindValue(":namaBelakang", namaBelakang);
    query.bindValue(":tanggalLahir", tanggalLahir);

    if (!query.exec())
        qFatal() << "Cannot add Member " << query.lastError().text();

    emit dataChanged();
}

void MemberRepository::edit(int kode, QString namaDepan, QString namaBelakang, QDate tanggalLahir)
{
    QSqlQuery query;
    query.prepare("UPDATE Member SET"
                  " nama_depan_member = :namaDepan,"
                  " nama_belakang_member = :namaBelakang,"
                  " tanggal_lahir = :tanggalLahir "
                  "WHERE kd_member = :kode");
    query.bindValue(":namaDepan", namaDepan);
    query.bindValue(":namaBelakang", namaBelakang);
    query.bindValue(":tanggalLahir",tanggalLahir);
    query.bindValue(":kode",kode);

    if(!query.exec())
        qFatal()<< "Cannot edit Member" << query.lastError().text();

    emit dataChanged();
}

void MemberRepository::remove(int kode)
{
    QSqlQuery query;
    query.prepare("DELETE from Member where kd_member = :kode");
    query.bindValue(":kode",kode);

    if(!query.exec())
        qFatal()<< "Cannot delete Member" << query.lastError().text();

    emit dataChanged();
}
