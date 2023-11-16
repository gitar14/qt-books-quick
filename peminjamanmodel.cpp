#include "peminjamanmodel.h"
#include "basepeminjamanbukumodel.h"
#include "usermanager.h"
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
    default:
        columnIndex = -1;
    }

    return QSqlQueryModel::data(index(item.row(), columnIndex), Qt::DisplayRole);
}

void PeminjamanModel::refresh()
{
    QSqlQuery query;

    if (!query.exec("SELECT "
                    "   Peminjaman.kd_peminjaman,"
                    "   Member.nama_depan_member,"
                    "   Member.nama_belakang_member,"
                    "   Peminjaman.kd_member,"
                    "   Peminjaman.tanggal_peminjaman,"
                    "   Peminjaman.lama_peminjaman "
                    "FROM Peminjaman "
                    "JOIN Member"
                    "   ON Member.kd_member = Peminjaman.kd_member"))
        qFatal() << "Cannot query Peminjaman " << query.lastError().text();

    setQuery(std::move(query));

    if (lastError().isValid())
        qFatal() << "Cannot move Peminjaman query " << lastError().text();
}

QString PeminjamanModel::add(QString kodeMember,QDate tanggal, int lama)
{
    QSqlQuery query;
    if (!query.exec("SELECT MAX(CAST(kd_peminjaman AS UNSIGNED)) FROM Peminjaman"))
        qFatal() << "Cannot query max Peminjaman kode " << query.lastError().text();

    int maxKode = -1;
    if (query.next()) {
        maxKode = query.value(0).toInt();
    }

    QString kode = QString::number(maxKode + 1).rightJustified(4, '0');
    query.prepare("INSERT INTO Peminjaman ("
                  " kd_peminjaman,"
                  " kd_member,"
                  " id_user,"
                  " tanggal_peminjaman, "
                  " lama_peminjaman "
                  ") VALUES ("
                  " :kode,"
                  " :member,"
                  " :user,"
                  " :tanggal,"
                  " :lama"
                  ")");
    query.bindValue(":kode", kode);
    query.bindValue(":user", UserManager::getInstance()->loggedUserId());
    query.bindValue(":member", kodeMember);
    query.bindValue(":tanggal", tanggal);
    query.bindValue(":lama", lama);

    if (!query.exec())
        qFatal() << "Cannot insert into Peminjaman " << query.lastError().text();

    refresh();

    return kode;
}

void PeminjamanModel::update(QString kode, QString kodeMember, QDate tanggal, int lama)
{
    QSqlQuery query;
    query.prepare("UPDATE Peminjaman SET "
                  " kd_member = :member, "
                  " tanggal_peminjaman = :tanggal, "
                  " lama_peminjaman = :lama "
                  "WHERE "
                  " kd_peminjaman = :kode"
                  );
    query.bindValue(":kode", kode);
    query.bindValue(":member", kodeMember);
    query.bindValue(":tanggal", tanggal);
    query.bindValue(":lama", lama);

    if (!query.exec())
        qFatal() << "Cannot update Peminjaman " << query.lastError().text();

    refresh();
}

void PeminjamanModel::remove(QString kode)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Peminjaman "
                  "WHERE kd_peminjaman = :kode");
    query.bindValue(":kode", kode);

    if (!query.exec())
        qFatal() << "Cannot remove peminjaman " << query.lastError().text();

    refresh();
}
