#ifndef PENGADAANMODEL_H
#define PENGADAANMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>

class PengadaanModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(QString textQuery READ textQuery WRITE seTextQuery NOTIFY textQueryChanged)
    QML_ELEMENT
public:
    enum Role {
        KodeRole = Qt::UserRole,
        SumberRole
    };

    explicit PengadaanModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    Q_INVOKABLE void refresh();
    Q_INVOKABLE int add(QString sumber);
    Q_INVOKABLE void update(int kode, QString sumber);
    Q_INVOKABLE void remove(int kode);
    QString textQuery() const;
    void seTextQuery(const QString &newTextQuery);
signals:
    void textQueryChanged();
private:
    QString mTextQuery;
};

#endif // PENGADAANMODEL_H
