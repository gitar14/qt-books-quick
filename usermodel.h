#ifndef USERMODEL_H
#define USERMODEL_H

#include <QtSql>
#include <QQmlEngine>

class UserModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(QString textQuery READ textQuery WRITE setTextQuery NOTIFY textQueryChanged)
    QML_ELEMENT
public:
    enum Role {
        idUserRole = Qt::UserRole,
        NamaRole,
        NamaDepanRole,
        NamaBelakangRole
    };

    explicit UserModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void addNew(QString idUser, QString namaDepan, QString namaBelakang, QString password);
    Q_INVOKABLE void edit(QString idUser, QString namaDepan, QString namaBelakang);
    Q_INVOKABLE void remove(QString idUser);
    Q_INVOKABLE int getIndexByKode(QString idUser);
    QString textQuery() const;
    void setTextQuery(const QString &newTextQuery);
signals:
    void textQueryChanged();
private:
    QString mTextQuery;
};

#endif // USERMODEL_H
