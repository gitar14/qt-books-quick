#include "basepengadaanbukumodel.h"
#include <QHash>
#include <QByteArray>

QHash<int, QByteArray> BasePengadaanBukuModel::getRoleNames()
{
    QHash<int, QByteArray> names;
    names[KodeBukuRole] = "kodeBuku";
    names[JumlahRole] = "jumlah";
    names[JudulBukuRole] = "judulBuku";
    return names;
}

