#ifndef BOOKLISTMODEL_H
#define BOOKLISTMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>

class BookListModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY queryChanged)
    QML_ELEMENT
public:
    enum Role {
        KodeRole = Qt::UserRole,
        JudulRole,
        PenulisRole,
        TahunTerbitRole,
        KategoriRole,
        PenerbitRole
    };

    explicit BookListModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    Q_INVOKABLE int getKodeByIndex(int index);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void addNew(
        QString judul,
        QString penulis,
        int jumlahBuku,
        int tahunTerbit,
        int kodeKategori,
        int kodePenerbit
    );
    Q_INVOKABLE void edit(
        int kode,
        QString judul,
        QString penulis,
        int jumlahHilang,
        int tahunTerbit,
        int kodeKategori,
        int kodePenerbit
    );
    Q_INVOKABLE void remove(int kode);
    Q_INVOKABLE void setIgnoredKodeList(QList<int> ignoredIdList);
    int count() const;

    QString textQuery() const;
    void setTextQuery(const QString &newQuery);

signals:
    void countChanged();

    void queryChanged();

private:
    QList<int> mIgnoredKodeList;
    QString mTextQuery;
};

#endif // BOOKLISTMODEL_H
