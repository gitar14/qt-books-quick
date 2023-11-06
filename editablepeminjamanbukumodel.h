#ifndef EDITABLEPEMINJAMANBUKUMODEL_H
#define EDITABLEPEMINJAMANBUKUMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>

class EditablePeminjamanBukuModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit EditablePeminjamanBukuModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;

    int rowCount(const QModelIndex &parent) const;

    Q_INVOKABLE void append(QString kodeBuku);

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    class Item {
    public:
        QString kodeBuku;
        QString judulBuku;
    };

    QList<Item> mItemList;
};

#endif // EDITABLEPEMINJAMANBUKUMODEL_H
