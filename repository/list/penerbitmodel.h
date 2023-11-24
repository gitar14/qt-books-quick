#ifndef PENERBITMODEL_H
#define PENERBITMODEL_H

#include <QSqlQueryModel>

class PenerbitModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum Role {
        KodeRole = Qt::UserRole,
        NamaRole,
        AlamatRole
    };

    explicit PenerbitModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &item, int role) const;

    void setTextQuery(const QString &newTextQuary);

public slots:
    void refresh();

private:
    QString mTextQuery;
};

#endif // PENERBITMODEL_H
