#ifndef BOOKLISTMODEL_H
#define BOOKLISTMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>

class BookListModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY queryChanged)
    Q_PROPERTY(int kategoriFilter READ kategoriFilter WRITE setKategoriFilter NOTIFY kategoriFilterChanged)
    Q_PROPERTY(int penerbitFilter READ penerbitFilter WRITE setPenerbitFilter NOTIFY penerbitFilterChanged)
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

    int kategoriFilter() const;
    void setKategoriFilter(int newKategoriFilter);

    int penerbitFilter() const;
    void setPenerbitFilter(int newPenerbitFilter);

signals:
    void countChanged();

    void queryChanged();

    void kategoriFilterChanged();

    void penerbitFilterChanged();

private:
    QList<int> mIgnoredKodeList;
    QString mTextQuery;
    int mKategoriFilter{-1};
    int mPenerbitFilter{-1};
};

#endif // BOOKLISTMODEL_H
