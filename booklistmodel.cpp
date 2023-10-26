#include "booklistmodel.h"

#include <QtSql>

BookListModel::BookListModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
}

QHash<int, QByteArray> BookListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Qt::UserRole] = "Kode";
    names[Qt::UserRole + 1] = "Judul";
    names[Qt::UserRole + 2] = "Pengarang";
    names[Qt::UserRole + 3] = "Penerbit";
    return names;
}

QVariant BookListModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole) return QSqlQueryModel::data(item, role);

    return data(index(item.row(), role - Qt::UserRole), Qt::DisplayRole);
}

QString BookListModel::getKodeByIndex(int index)
{
    return record(index).field(0).value().toString();
}

void BookListModel::refresh()
{
    QSqlQuery query;
    if (!query.exec("SELECT Kode_Buku, Judul, Pengarang, Penerbit.Nm_penerbit FROM Buku JOIN Penerbit on Penerbit.Kode_Penerbit = Buku.Kode_Penerbit"))
        qFatal() << query.lastError().text();

    setQuery(std::move(query));
    if (lastError().isValid())
        qFatal() << lastError().text();
}
