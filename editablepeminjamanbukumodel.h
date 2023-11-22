#ifndef EDITABLEPEMINJAMANBUKUMODEL_H
#define EDITABLEPEMINJAMANBUKUMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>

class EditablePeminjamanBukuModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<int> kodeBukuList READ getKodeBukuList NOTIFY itemsChanged)
    Q_PROPERTY(bool isBukuAvailable READ isBukuAvailable NOTIFY itemsChanged)
    Q_PROPERTY(int totalDenda READ totalDenda NOTIFY totalDendaChanged)
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

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    int totalDenda() const;

signals:
    void itemsChanged();
    void totalDendaChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    class Item {
    public:
        int kodeBuku;
        QString judulBuku;
        int denda;
    };

    void refresh();

    QList<Item> mItemList;
    bool mBukuAvailable;
};

#endif // EDITABLEPEMINJAMANBUKUMODEL_H
