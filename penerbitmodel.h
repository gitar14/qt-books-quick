#ifndef PENERBITMODEL_H
#define PENERBITMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>

class PenerbitModel : public QSqlQueryModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum Role {
        KodeRole = Qt::UserRole,
        NamaRole,
        AlamatRole
    };

    explicit PenerbitModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    Q_INVOKABLE void add(QString nama, QString alamat);
    Q_INVOKABLE void edit(QString kode, QString nama, QString alamat);

    void refresh();
};

#endif // PENERBITMODEL_H
