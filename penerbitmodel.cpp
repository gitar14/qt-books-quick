#include "penerbitmodel.h"

PenerbitModel::PenerbitModel(QObject *parent)
    : QSqlQueryModel{parent}
{
    QSqlQuery query;
    if (!query.exec("SELECT * FROM Penerbit"))
        qFatal("Cannot query Penerbit: %s", qPrintable(query.lastError().text()));

    setQuery(std::move(query));

    if (lastError().isValid()) {
        qFatal("Cannot move penerbit query: %s", qPrintable(lastError().text()));
    }
}

QHash<int, QByteArray> PenerbitModel::roleNames() const
{
    QHash<int, QByteArray> names;
    for (int i = 0; i < this->record().count(); i ++) {
        names.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
    }
    return names;
}

QVariant PenerbitModel::data(const QModelIndex &item, int role) const
{
    QVariant value;

    if (item.isValid()) {
        if (role < Qt::UserRole) {
            value = QSqlQueryModel::data(item, role);
        } else {
            int columnIdx = role - Qt::UserRole - 1;
            QModelIndex modelIndex = this->index(item.row(), columnIdx);
            value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        }
    }
    return value;
}
