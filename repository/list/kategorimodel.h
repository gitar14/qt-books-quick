#ifndef KATEGORIMODEL_H
#define KATEGORIMODEL_H

#include <QtSql>

class KategoriModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum Role {
        KodeRole = Qt::UserRole,
        JenisRole
    };

    explicit KategoriModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    void setTextQuery(const QString &newTextQuery);
public slots:
    void refresh();
private:
    QString mTextQuery;
};

#endif // KATEGORIMODEL_H
