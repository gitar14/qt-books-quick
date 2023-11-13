import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import my.id.levirs.books

RowLayout {
    PeminjamanBukuModel {
        id: peminjamanBukuModel
        kodePeminjaman: peminjamanDetailFrame.peminjamanKode
    }

    EditablePeminjamanBukuModel {
        id: editablePeminjamanBukuModel
//        onItemsChanged: peminjamanBukuListModel.setIgnoredKodeList(kodeBukuList)
    }

    PeminjamanModel {
        id: peminjamanModel
    }

    BookListModel {
        id: peminjamanBukuListModel
    }

    MemberModel {
        id: memberModel
    }

    PeminjamanList {
        onAddClicked: editPeminjamanDialog.open()
        listModel: peminjamanModel
    }

    PeminjamanEditDialog{
        id: editPeminjamanDialog
        peminjamanBukuModel: editablePeminjamanBukuModel
        bukuModel: peminjamanBukuListModel
        memberModel: memberModel
        onAccepted: {
            if (peminjamanKode == "") {
                peminjamanKode = peminjamanmodel.add(peminjamanSumber);
                peminjamanBukuModel.addAll(peminjamanKode, editablePeminjamanBukuModel);
            } else {
                peminjamanModel.update(peminjamanKode, peminjamanSumber);
                peminjamanBukuModel.updateALL(editablePeminjamanBukuModel)
            }
        }
    }

    PeminjamanDetailFrame{
        id: peminjamanDetailFrame
        peminjamanBukuModel: peminjamanBukuModel
    }
}
