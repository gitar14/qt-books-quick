#ifndef KATEGORIMODEL_H
#define KATEGORIMODEL_H

#include <QtSql>

class KategoriModel : public QSqlQueryModel
{
public:
    enum Role {
        KodeRole = Qt::UserRole,
        JenisRole
    };

    explicit KategoriModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;
};

#endif // KATEGORIMODEL_H
