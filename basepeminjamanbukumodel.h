#ifndef BASEPEMINJAMANBUKUMODEL_H
#define BASEPEMINJAMANBUKUMODEL_H

#include <Qt>

namespace BasePeminjamanBukuModel {
    enum Role {
        KodeBukuRole = Qt::UserRole,
        JudulBukuRole
    };

    QHash<int, QByteArray> getRoleNames();
}

#endif // BASEPEMINJAMANBUKUMODEL_H
