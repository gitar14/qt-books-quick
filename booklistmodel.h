#ifndef BOOKLISTMODEL_H
#define BOOKLISTMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>

class BookListModel : public QSqlQueryModel
{
    Q_OBJECT
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

    Q_INVOKABLE QString getKodeByIndex(int index);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void addNew(
        QString judul,
        QString penulis,
        int jumlahBuku,
        int tahunTerbit,
        QString kodeKategori,
        QString kodePenerbit
    );
    Q_INVOKABLE void edit(
        QString kode,
        QString judul,
        QString penulis,
        int jumlahBuku,
        int tahunTerbit,
        QString kodeKategori,
        QString kodePenerbit
    );
    Q_INVOKABLE void remove(QString kode);
    Q_INVOKABLE void setIgnoredKodeList(QStringList ignoredIdList);
private:
    QStringList mIgnoredKodeList;
};

#endif // BOOKLISTMODEL_H
