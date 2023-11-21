#ifndef PENGADAANBUKUMODEL_H
#define PENGADAANBUKUMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>
#include "basepengadaanbukumodel.h"

class PengadaanBukuModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(int kodePengadaan READ kodePengadaan WRITE setKodePengadaan NOTIFY kodePengadaanChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    QML_ELEMENT
public:
    explicit PengadaanBukuModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    void refresh();
    int kodePengadaan() const;
    void setKodePengadaan(const int &newKodePengadaan);

    Q_INVOKABLE void updateAll(QAbstractItemModel* model);
    Q_INVOKABLE void addAll(int kodePengadaan, QAbstractItemModel* model);
    Q_INVOKABLE void removeAll();
    int count() const;

signals:
    void kodePengadaanChanged();
    void countChanged();

private:
    int mKodePengadaan;

    void internalUpdateAll(int kodePengadaan, QAbstractItemModel* model);
};

#endif // PENGADAANBUKUMODEL_H
