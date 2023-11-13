#ifndef PEMINJAMANMODEL_H
#define PEMINJAMANMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>

class PeminjamanModel : public QSqlQueryModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum Role {
        KodeRole = Qt::UserRole,
        TanggalRole,
        LamaRole
    };

    explicit PeminjamanModel (QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &item, int role) const;

    Q_INVOKABLE void refresh();
    Q_INVOKABLE QString add(QString sumber);
    Q_INVOKABLE void update(QString kode, QString sumber);
    Q_INVOKABLE void remove(QString kode);
};

#endif // PEMINJAMANMODEL_H
