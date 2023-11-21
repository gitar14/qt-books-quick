#include "basepeminjamanbukumodel.h"
#include <QHash>

QHash<int, QByteArray> BasePeminjamanBukuModel::getRoleNames()
{
    QHash<int, QByteArray> roles;
    roles[KodeBukuRole] = "kodeBuku";
    roles[JudulBukuRole] = "judulBuku";
    roles[DendaRole] = "denda";
    return roles;
}
