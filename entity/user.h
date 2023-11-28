#ifndef USER_H
#define USER_H

#include <QObject>

class UserData : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT FINAL)
    Q_PROPERTY(QString namaDepan READ namaDepan CONSTANT FINAL)
    Q_PROPERTY(QString namaBelakang READ namaBelakang CONSTANT FINAL)
    Q_PROPERTY(UserRole role READ role CONSTANT FINAL)
public:
    enum UserRole {
        AdminRole = 0,
        PegawaiRole
    };

    UserData(const QString &id = "",
             const QString &namaDepan = "",
             const QString &namaBelakang = "",
             UserRole role = AdminRole);

    QString id() const;
    QString namaDepan() const;
    QString namaBelakang() const;
    UserRole role() const;

private:
    QString mId;
    QString mNamaDepan;
    QString mNamaBelakang;
    UserRole mUserRole;
    UserRole mRole;
};

#endif // USER_H
