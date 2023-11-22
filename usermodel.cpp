#include "usermodel.h"
#include "sqlhelper.h"
#include "usermanager.h"

UserModel::UserModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
}

QHash<int, QByteArray> UserModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[idUserRole] = "idUser";
    names[NamaRole] = "name";
    names[NamaDepanRole] = "namaDepan";
    names[NamaBelakangRole] = "namaBelakang";
    return names;
}

QVariant UserModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(item, role);

    int row= item.row();
    int columnIndex;
    switch (role) {
    case idUserRole:
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
    default:
        columnIndex = -1;
    }

    return QSqlQueryModel::data(index(row, columnIndex), Qt::DisplayRole);
}

void UserModel::refresh()
{
    QHash<QString, QVariant> binds;
    QString queryString = "SELECT"
                          "   id_user,"
                          "   nama_depan_user, "
                          "   nama_belakang_user "
                          "FROM User "
                          "WHERE role = 1";
    if (mTextQuery.length()>0) {
        queryString += " WHERE (nama_depan_user || ' ' || nama_belakang_user) LIKE :textQuery";
        binds[":textQuery"]="%"+ mTextQuery +"%";
    }

    QSqlQuery query;
    query.prepare(queryString);

    SQLHelper::applyBindMaps(query, binds);

    if (!query.exec())
        qFatal("Cannot query User: %s", qPrintable(query.lastError().text()));

    setQuery(std::move(query));

    if (lastError().isValid()) {
        qFatal("Cannot move User query: %s", qPrintable(lastError().text()));
    }
}

void UserModel::addNew(QString idUser, QString namaDepan, QString namaBelakang, QString password)
{
    UserManager::getInstance()->addUser(idUser, namaDepan, namaBelakang, UserManager::PegawaiRole, password);

    refresh();
}

void UserModel::edit(QString idUser, QString namaDepan, QString namaBelakang)
{
    QSqlQuery query;

    query.prepare("UPDATE User SET "
                  " nama_depan_user = :namaDepan,"
                  " nama_belakang_user = :namaBelakang "
                  "WHERE id_user = :idUser");

    query.bindValue(":idUser", idUser);
    query.bindValue(":namaDepan", namaDepan);
    query.bindValue(":namaBelakang", namaBelakang);

    if (!query.exec())
        qFatal() << "Cannot edit User " << query.lastError().text();

    refresh();
}

void UserModel::remove(QString idUser)
{
    QSqlQuery query;

    query.prepare("DELETE FROM User WHERE id_user = :idUser");

    query.bindValue(":idUser", idUser);

    if (!query.exec())
        qFatal() << "Cannot remove User " << query.lastError().text();

    refresh();
}

QString UserModel::textQuery() const
{
    return mTextQuery;
}

void UserModel::setTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    refresh();
    emit textQueryChanged();
}
