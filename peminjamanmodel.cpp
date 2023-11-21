#include "peminjamanmodel.h"
#include "basepeminjamanbukumodel.h"
#include "usermanager.h"
#include "sqlhelper.h"
#include <QtSql>

PeminjamanModel::PeminjamanModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
}
QHash<int, QByteArray> PeminjamanModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[KodeRole] = "kode";
    names[KodeMemberRole] = "kodeMember";
    names[NamaMemberRole] = "namaMember";
    names[TanggalRole] = "tanggal";
    names[LamaRole] = "lama";
    names[TanggalTenggatRole] = "tanggalTenggat";
    names[TanggalPengembalianRole] = "tanggalPengembalian";
    names[SudahDikembalikanRole] = "sudahDikembalikan";
    return names;
}

QVariant PeminjamanModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(item, role);

    int columnIndex = -1;
    switch (role) {
    case KodeRole:
        columnIndex = 0;
        break;
    case NamaMemberRole:
        return QSqlQueryModel::data(index(item.row(), 1)).toString() + " " +
               QSqlQueryModel::data(index(item.row(), 2)).toString();
    case KodeMemberRole:
        columnIndex = 3;
        break;
    case TanggalRole:
        columnIndex = 4;
        break;
    case LamaRole:
        columnIndex = 5;
        break;
    case TanggalTenggatRole:
        return data(item, TanggalRole).toDate().addDays(data(item, LamaRole).toInt());
    case TanggalPengembalianRole:
        return QSqlQueryModel::data(index(item.row(), 6)).toDate();
    case SudahDikembalikanRole:
        return data(item, TanggalPengembalianRole).toDate().isValid();
    default:
        columnIndex = -1;
    }

    return QSqlQueryModel::data(index(item.row(), columnIndex), Qt::DisplayRole);
}

void PeminjamanModel::refresh()
{
    QSqlQuery query;

    if (!query.exec("SELECT "
                    "   Detail_Peminjaman.kd_detail_peminjaman,"
                    "   Member.nama_depan_member,"
                    "   Member.nama_belakang_member,"
                    "   Detail_Peminjaman.kd_member,"
                    "   Detail_Peminjaman.tanggal_peminjaman,"
                    "   Detail_Peminjaman.lama_peminjaman,"
                    "   Detail_Peminjaman.tanggal_pengembalian "
                    "FROM Detail_Peminjaman "
                    "JOIN Member"
                    "   ON Member.kd_member = Detail_Peminjaman.kd_member"))
        qFatal() << "Cannot query Peminjaman " << query.lastError().text();

    setQuery(std::move(query));

    if (lastError().isValid())
        qFatal() << "Cannot move Peminjaman query " << lastError().text();
}

int PeminjamanModel::add(int kodeMember,QDate tanggal, int lama)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Detail_Peminjaman ("
                  " kd_member,"
                  " id_user,"
                  " tanggal_peminjaman, "
                  " lama_peminjaman "
                  ") VALUES ("
                  " :member,"
                  " :user,"
                  " :tanggal,"
                  " :lama"
                  ")");
    query.bindValue(":user", UserManager::getInstance()->loggedUserId());
    query.bindValue(":member", kodeMember);
    query.bindValue(":tanggal", tanggal);
    query.bindValue(":lama", lama);

    if (!query.exec())
        qFatal() << "Cannot insert into Peminjaman " << query.lastError().text();

    refresh();

    return query.lastInsertId().toInt();
}

void PeminjamanModel::update(int kode, int kodeMember, QDate tanggal, int lama)
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

    refresh();
}

void PeminjamanModel::remove(int kode)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Detail_Peminjaman "
                  "WHERE kd_detail_peminjaman = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot remove peminjaman " << query.lastError().text();

    refresh();
}

void PeminjamanModel::tandaiDikembalikan(int kode, QDate tanggal, int denda)
{
    QSqlQuery query;
    query.prepare("UPDATE Detail_Peminjaman "
                  "SET tanggal_pengembalian = :pengembalian "
                  "WHERE kd_detail_peminjaman = :kode");
    query.bindValue(":kode", kode);
    query.bindValue(":pengembalian", tanggal);

    if (!query.exec())
        qFatal() << "Cannot add Pengembalian " << query.lastError().text();

    refresh();
}

void PeminjamanModel::tandaiBelumDikembalikan(int kode)
{
    QSqlQuery query;
    query.prepare("UPDATE Detail_Peminjaman "
                  "SET tanggal_pengembalian = NULL "
                  "WHERE kd_detail_peminjaman = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot remove Pengembalian " << query.lastError().text();

    refresh();
}
