#include "memberrepository.h"
#include "sqlhelper.h"
#include <QSqlQuery>
#include <QSqlError>

MemberData::MemberData(
    int kode,
    const QString &namaDepan,
    const QString &namaBelakang,
    const QDate &tanggalLahir
    )
    : QObject(),
    mKode(kode),
    mNamaDepan(namaDepan),
    mNamaBelakang(namaBelakang),
    mTanggalLahir(tanggalLahir)
{}


int MemberData::kode() const
{
    return mKode;
}

QString MemberData::namaDepan() const
{
    return mNamaDepan;
}

QString MemberData::namaBelakang() const
{
    return mNamaBelakang;
}

QDate MemberData::tanggalLahir() const
{
    return mTanggalLahir;
}


MemberRepository::MemberRepository(QObject *parent)
    : QObject{parent}
{

}

QList<MemberData *> MemberRepository::getAll(QString textQuery)
{
    QHash<QString,QVariant>binds;
    QString queryString = "SELECT "
                          "   kd_member,"
                          "   nama_depan_member,"
                          "   nama_belakang_member,"
                          "   tanggal_lahir "
                          "FROM Member";
    if (textQuery.length() > 0) {
        queryString += " WHERE (nama_depan_member || ' ' || nama_belakang_member) LIKE :textQuery";
        binds[":textQuery"]="%"+ textQuery +"%";
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
            query.value(2).toString(),
            query.value(3).toDate()
            ));
    }

    return result;
}

MemberData *MemberRepository::get(int kode)
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

    return query.next() ? new MemberData(
        query.value(0).toInt(),
        query.value(1).toString(),
        query.value(2).toString(),
        query.value(3).toDate()
               ) : new MemberData();
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
