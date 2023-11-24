#ifndef KATEGORIEDITVIEWMODEL_H
#define KATEGORIEDITVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>

class KategoriEditViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int kode READ kode WRITE setKode NOTIFY kodeChanged)
    Q_PROPERTY(QString nama READ nama WRITE setNama NOTIFY namaChanged)
    Q_PROPERTY(int namaMaxLength READ namaMaxlength CONSTANT)
    Q_PROPERTY(int namaAvailableLength READ namaAvailableLength NOTIFY namaChanged)
    Q_PROPERTY(QString namaError READ namaError NOTIFY namaChanged)
    QML_ELEMENT
public:
    explicit KategoriEditViewModel(QObject *parent = nullptr);


    int kode() const;
    void setKode(int newKode);

    QString nama() const;
    void setNama(const QString &newNama);

    int namaMaxlength() const;
    int namaAvailableLength() const;
    QString namaError() const;

    Q_INVOKABLE void submit();

signals:

    void kodeChanged();
    void namaChanged();

private:
    int mKode;
    QString mNama;
};

#endif // KATEGORIEDITVIEWMODEL_H
