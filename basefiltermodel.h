#ifndef BASEFILTERMODEL_H
#define BASEFILTERMODEL_H

#include <QAbstractProxyModel>

class BaseFilterModel : public QAbstractProxyModel
{
    Q_OBJECT
public:
    explicit BaseFilterModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &item, int role) const override;
    virtual QVariant getFirstData(const QModelIndex &item, int role) const = 0;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
};

#endif // BASEFILTERMODEL_H
