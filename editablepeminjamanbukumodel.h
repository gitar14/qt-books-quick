#ifndef EDITABLEPEMINJAMANBUKUMODEL_H
#define EDITABLEPEMINJAMANBUKUMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>

class EditablePeminjamanBukuModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<int> kodeBukuList READ getKodeBukuList NOTIFY itemsChanged)
    Q_PROPERTY(bool isBukuAvailable READ isBukuAvailable NOTIFY itemsChanged)
    QML_ELEMENT
public:
    explicit EditablePeminjamanBukuModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const;

    QList<int> getKodeBukuList();


    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void append(int kodeBuku);
    Q_INVOKABLE void populateFrom(QAbstractItemModel *model);
    bool isBukuAvailable() const;

signals:
    void itemsChanged();
protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    class Item {
    public:
        int kodeBuku;
        QString judulBuku;
    };

    void refresh();

    QList<Item> mItemList;
    bool mBukuAvailable;
};

#endif // EDITABLEPEMINJAMANBUKUMODEL_H
