#include "membermodel.h"
#include <QtSql>

MemberModel::MemberModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
}

QHash<int, QByteArray> MemberModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[KodeRole] = "kode";
    names[NamaRole] = "name";
    names[TglLahirRole] = "tanggalLahir";
    return names;
}

QVariant MemberModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(item, role);

    int columnIndex;
    switch (role) {
    case KodeRole:
        columnIndex = 0;
        break;
    case NamaRole:
        columnIndex = 1;
        break;
    case TglLahirRole:
        columnIndex = 2;
        break;
    default:
        columnIndex = -1;
    }

    return QSqlQueryModel::data(index(item.row(), columnIndex), Qt::DisplayRole);
}

void MemberModel::add(QString nama, QString tgl_lahir)
{
    QSqlQuery query;
    if (!query.exec("SELECT MAX(CAST(kd_member AS UNSIGNED)) FROM Member"))
        qFatal() << "Cannot get max id " << query.lastError().text();

    int maxId = -1;
    if (query.next()) {
        maxId = query.value(0).toInt();
    }

    query.prepare("INSERT INTO Member("
                  " kd_member,"
                  " nama_member,"
                  " tgl_lahir"
                  ") VALUES ("
                  " :kode,"
                  " :nama,"
                  " :tanggalLahir"
                  ")");

    query.bindValue(":kode", QString::number(maxId + 1).rightJustified(4, '0'));
    query.bindValue(":nama", nama);
    query.bindValue(":tanggalLahir", tgl_lahir);

    if (!query.exec())
        qFatal() << "Cannot add Member " << query.lastError().text();

    refresh();
}

void MemberModel::edit(QString kode, QString nama, QString tanggalLahir)
{
    QSqlQuery query;
    query.prepare("UPDATE Member SET"
                  " nama_member = :nama,"
                  " tgl_lahir = :tanggalLahir "
                  "WHERE kd_member = :kode");
    query.bindValue(":nama",nama);
    query.bindValue(":tanggalLahir",tanggalLahir);
    query.bindValue(":kode",kode);

    if(!query.exec())
        qFatal()<< "Cannot edit Member" << query.lastError().text();

    refresh();
}

void MemberModel::remove(QString kode)
{
    QSqlQuery query;
    query.prepare("DELETE from Member where kd_member = :kode");
    query.bindValue(":kode",kode);

    if(!query.exec())
        qFatal()<< "Cannot delete Member" << query.lastError().text();

    refresh();
}

void MemberModel::refresh()
{
    QSqlQuery query;
    if (!query.exec("SELECT "
                    "   kd_member,"
                    "   nama_member,"
                    "   tgl_lahir "
                    "FROM Member"))
        qFatal() << "Cannot select from Member" << query.lastError().text();

    setQuery(std::move(query));
}
