#ifndef BUKULISTMODEL_H
#define BUKULISTMODEL_H

#include <QSqlQueryModel>

class BukuListModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum Role {
        KodeRole = Qt::UserRole,
        JudulRole,
        PenulisRole,
        TahunTerbitRole,
        KategoriRole,
        PenerbitRole
    };

    explicit BukuListModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    void setIgnoredKodeList(QList<int> ignoredIdList);
    void setTextQuery(const QString &newQuery);
    void setKategoriFilter(int newKategoriFilter);
    void setPenerbitFilter(int newPenerbitFilter);

public slots:
    void refresh();

private:
    QList<int> mIgnoredKodeList;
    QString mTextQuery;
    int mKategoriFilter{-1};
    int mPenerbitFilter{-1};
};

#endif // BUKULISTMODEL_H
