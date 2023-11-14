#ifndef MEMBERMODEL_H
#define MEMBERMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>

class MemberModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(QString textQuery READ TextQuery WRITE setTextQuery NOTIFY textQueryChanged)
    QML_ELEMENT
public:
    enum Role {
        KodeRole = Qt::UserRole,
        NamaRole,
        NamaDepanRole,
        NamaBelakangRole,
        TanggalLahirRole
    };

    explicit MemberModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    Q_INVOKABLE void add(QString namaDepan, QString namaBelakang, QDate tanggalLahir);
    Q_INVOKABLE void edit(QString kode, QString namaDepan, QString namaBelakang, QDate tanggalLahir);
    Q_INVOKABLE void remove(QString kode);
    void refresh();
    QString TextQuery() const;
    void setTextQuery(const QString &newTextQuery);
signals:
    void textQueryChanged();
private:
    QString mTextQuery;
};

#endif // PENERBITMODEL_H
