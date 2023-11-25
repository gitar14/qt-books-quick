#include "pengadaanmodel.h"
#include "basepengadaanbukumodel.h"
#include <QtSql>
#include "sqlhelper.h"
#include "usermanager.h"

PengadaanModel::PengadaanModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    refresh();
}

QHash<int, QByteArray> PengadaanModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[KodeRole] = "kode";
    names[SumberRole] = "sumber";
    names[TanggalPengadaanRole] = "tanggalPengadaan";
    return names;
}

QVariant PengadaanModel::data(const QModelIndex &item, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(item, role);

    int columnIndex = -1;
    switch (role) {
    case KodeRole:
        columnIndex = 0;
        break;
    case SumberRole:
        columnIndex = 1;
        break;
    case TanggalPengadaanRole:
        columnIndex = 2;
        break;
    }

    return QSqlQueryModel::data(index(item.row(), columnIndex), Qt::DisplayRole);
}

void PengadaanModel::refresh()
{

    setQuery(std::move(query));

    if (lastError().isValid())
        qFatal() << "Cannot move Pengadaan query " << lastError().text();
}

QString PengadaanModel::textQuery() const
{
    return mTextQuery;
}

void PengadaanModel::seTextQuery(const QString &newTextQuery)
{
    if (mTextQuery == newTextQuery)
        return;
    mTextQuery = newTextQuery;
    emit textQueryChanged();
    refresh ();
}
