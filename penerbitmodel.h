#ifndef PENERBITMODEL_H
#define PENERBITMODEL_H

#include <QtSql>

class PenerbitModel : public QSqlQueryModel
{
public:
    explicit PenerbitModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;
};

#endif // PENERBITMODEL_H
