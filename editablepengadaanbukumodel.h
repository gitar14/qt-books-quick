#ifndef EDITABLEPENGADAANBUKUMODEL_H
#define EDITABLEPENGADAANBUKUMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>

class EditablePengadaanBukuModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList kodeBukuList READ getKodeBukuList NOTIFY itemsChanged)
    Q_PROPERTY(bool isBukuAvailable READ isBukuAvailable NOTIFY itemsChanged)
    QML_ELEMENT
public:    
    explicit EditablePengadaanBukuModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;


    QStringList getKodeBukuList();

    Q_INVOKABLE void append(QString kodeBuku, int jumlah);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void populateFrom(QAbstractItemModel *model);
    bool isBukuAvailable() const;

signals:
    void itemsChanged();
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    class PengadaanBukuItem {
    public:
        QString kodeBuku;
        int jumlah;
        QString judulBuku;
    };

    void refresh();

    QList<PengadaanBukuItem> mItemList;
    bool mBukuAvailable;
};

#endif // EDITABLEPENGADAANBUKUMODEL_H
