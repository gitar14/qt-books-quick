#ifndef PENGADAANMODEL_H
#define PENGADAANMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>

class PengadaanModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum Role {
        KodeRole = Qt::UserRole,
        SumberRole,
        TanggalPengadaanRole
    };

    explicit PengadaanModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    void seTextQuery(const QString &newTextQuery);
public slots:
    void refresh();
signals:
    void textQueryChanged();
private:
    QString mTextQuery;
};

#endif // PENGADAANMODEL_H
