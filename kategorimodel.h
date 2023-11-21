#ifndef KATEGORIMODEL_H
#define KATEGORIMODEL_H

#include <QtSql>
#include <QQmlEngine>

class KategoriModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged)
    QML_ELEMENT
public:
    enum Role {
        KodeRole = Qt::UserRole,
        JenisRole
    };

    explicit KategoriModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void addNew(QString jenis);
    Q_INVOKABLE void edit(int kode, QString jenis);
    Q_INVOKABLE void remove(int kode);
    Q_INVOKABLE int getIndexByKode(int kode);
    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);
signals:
    void textQueryChanged();
private:
    QString mTextQuery;
};

#endif // KATEGORIMODEL_H
