#ifndef PEMINJAMANBUKUMODEL_H
#define PEMINJAMANBUKUMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>

class PeminjamanBukuModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(QString kodePeminjaman READ kodePeminjaman WRITE setKodePeminjaman NOTIFY kodePeminjamanChanged)
    QML_ELEMENT
public:
    explicit PeminjamanBukuModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &item, int role) const;

    Q_INVOKABLE void refresh();

    QString kodePeminjaman() const;
    void setKodePeminjaman(const QString &newKodePeminjaman);

signals:
    void kodePeminjamanChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QString mKodePeminjaman;
};

#endif // PEMINJAMANBUKUMODEL_H
