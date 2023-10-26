#ifndef KATEGORIMODEL_H
#define KATEGORIMODEL_H

#include <QtSql>
#include <QQmlEngine>

class KategoriModel : public QSqlQueryModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum Role {
        KodeRole = Qt::UserRole,
        JenisRole
    };

    explicit KategoriModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void addNew(QString jenis);
    Q_INVOKABLE void edit(QString kode, QString jenis);
    Q_INVOKABLE void remove(QString kode);
};

#endif // KATEGORIMODEL_H
