import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import my.id.levirs.books

RowLayout {
//    PeminjamanBukuModel {
//        id: peminjamanBukuModel
//        kodePeminjaman: peminjamanDetailFrame.peminjamanKode
//    }

//    EditablePeminjamanBukuModel {
//        id: edittablePengadaanBukuModel
//        onItemsChanged: peminjamanBukuListModel.setIgnoredKodeList(kodeBukuList)
//    }

//    PeminjamanModel {
//        id: peminjamanModel
//    }

    ListModel {
        id: peminjamanModel

        ListElement {
            namaMember: "Dida"
            tanggalPinjam: "18 JAN"
            tenggatPinjam: "23 noV"
        }

        ListElement {
            namaMember: "Jepe"
            tanggalPinjam: "12 April"
            tenggatPinjam: "12 Jan"
        }

        ListElement {
            namaMember: "Akmul"
            tanggalPinjam: "14 Des"
            tenggatPinjam: "14 Feb"
        }
    }

    BookListModel {
        id: peminjamanBukuListModel
    }

//    PengadaanListModel {
//        id: peminjamanListModel
//    }
    PeminjamanList{
        onAddClicked: editPeminjamanDialog.open()
        listModel: peminjamanModel
    }

    PeminjamanEditDialog{
        id: editPeminjamanDialog
//        peminjamanBukuModel: editablePeminjamanBukuModel
        bukuModel: peminjamanBukuListModel
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
    }
}
