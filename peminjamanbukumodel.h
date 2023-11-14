#ifndef PEMINJAMANBUKUMODEL_H
#define PEMINJAMANBUKUMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>
#include <QByteArray>
#include "basepeminjamanbukumodel.h"

class PeminjamanBukuModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(QString kodePeminjaman READ kodePeminjaman WRITE setKodePeminjaman NOTIFY kodePeminjamanChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    QML_ELEMENT
public:
    explicit PeminjamanBukuModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &item, int role) const;

    void refresh();
    QString kodePeminjaman() const;
    void setKodePeminjaman(const QString &newKodePeminjaman);

    Q_INVOKABLE void updateAll(QAbstractItemModel* model);
    Q_INVOKABLE void addAll(QString kodePengadaan, QAbstractItemModel* model);
    Q_INVOKABLE void removeAll();
    int count() const;

signals:
    void kodePeminjamanChanged();
    void countChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QString mKodePeminjaman;

    void internalUpdateAll(QString kodePeminjaman, QAbstractItemModel*model);
};

#endif // PEMINJAMANBUKUMODEL_H
