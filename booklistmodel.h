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
    };

    explicit BookListModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    Q_INVOKABLE QString getKodeByIndex(int index);
    Q_INVOKABLE void refresh();
};

#endif // BOOKLISTMODEL_H
