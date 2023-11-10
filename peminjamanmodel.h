#ifndef PEMINJAMANMODEL_H
#define PEMINJAMANMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>

class PeminjamanModel : public QSqlQueryModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit PeminjamanModel(QObject *parent = nullptr);
};

#endif // PEMINJAMANMODEL_H
