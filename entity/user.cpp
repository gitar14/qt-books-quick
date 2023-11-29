#include "user.h"

UserData::UserData(const QString &id,
                   const QString &namaDepan,
                   const QString &namaBelakang,
                   UserRole role)
    : QObject(),
    mId(id),
    mNamaDepan(namaDepan),
    mNamaBelakang(namaBelakang),
    mRole{role}
{}


QString UserData::id() const
{
    return mId;
}

QString UserData::namaDepan() const
{
    return mNamaDepan;
}

QString UserData::namaBelakang() const
{
    return mNamaBelakang;
}

UserData::UserRole UserData::role() const
{
    return mRole;
}

QString UserData::nama() const
{
    return mNamaDepan + " " + mNamaBelakang;
}
