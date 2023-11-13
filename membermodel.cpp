#include "membermodel.h"
#include "sqlhelper.h"
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
    names[NamaDepanRole] = "namaDepan";
    names[NamaBelakangRole] = "namaBelakang";
    names[TanggalLahirRole] = "tanggalLahir";
    return names;
}

QVariant MemberModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(item, role);

    int row= item.row();
    int columnIndex;
    switch (role) {
    case KodeRole:
        columnIndex = 0;
        break;
    case NamaRole:
        return QSqlQueryModel::data(index(row, 1)).toString()+" "+QSqlQueryModel::data(index(row, 2)).toString();
    case NamaDepanRole:
        columnIndex = 1;
        break;
    case NamaBelakangRole:
        columnIndex = 2;
        break;
    case TanggalLahirRole:
        columnIndex = 3;
        break;
    default:
        columnIndex = -1;
    }

    return QSqlQueryModel::data(index(row, columnIndex), Qt::DisplayRole);
}

void MemberModel::add(QString namaDepan, QString namaBelakang, QDate tanggalLahir)
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
                  " nama_depan_member,"
                  " nama_belakang_member,"
                  " tanggal_lahir"
                  ") VALUES ("
                  " :kode,"
                  " :namaDepan,"
                  " :namaBelakang,"
                  " :tanggalLahir"
                  ")");

    query.bindValue(":kode", QString::number(maxId + 1).rightJustified(4, '0'));
    query.bindValue(":namaDepan", namaDepan);
    query.bindValue(":namaBelakang", namaBelakang);
    query.bindValue(":tanggalLahir", tanggalLahir);

    if (!query.exec())
        qFatal() << "Cannot add Member " << query.lastError().text();

    refresh();
}

void MemberModel::edit(QString kode, QString namaDepan, QString namaBelakang, QDate tanggalLahir)
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
    QHash<QString,QVariant>binds;
    QString queryString = "SELECT "
                          "   kd_member,"
                          "   nama_depan_member,"
                          "   nama_belakang_member,"
                          "   tanggal_lahir "
                          "FROM Member";
    if (mTextQuery.length()>0) {
        queryString += " WHERE (nama_depan_member || ' ' || nama_belakang_member) LIKE :textQuery";
        binds[":textQuery"]="%"+ mTextQuery +"%";
    }

    QSqlQuery query;
    query.prepare(queryString);
    SQLHelper::applyBindMaps(query,binds);

    if (!query.exec())
        qFatal() << "Cannot select from Member" << query.lastError().text();

    setQuery(std::move(query));
}

QString MemberModel::TextQuery() const
{
    return mTextQuery;
}

void MemberModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    emit textQueryChanged();
    refresh();
}
