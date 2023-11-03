import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import my.id.levirs.books

RowLayout {
    PengadaanBukuModel {
        id: pengadaanBukuModel
        kodePengadaan: pengadaanDetailFrame.pengadaanKode
    }

    EditablePengadaanBukuModel {
        id: editablePengadaanBukuModel

        onItemsChanged: pengadaanBukuListModel.setIgnoredKodeList(kodeBukuList)
    }

    PengadaanModel {
        id: pengadaanModel
    }

    BookListModel {
        id: pengadaanBukuListModel
    }

    PengadaanList {
        listModel: pengadaanModel
        onAddClicked: {
            editPengadaanDialog.pengadaanKode = ""
            editPengadaanDialog.pengadaanSumber = ""
            editablePengadaanBukuModel.clear();
            editPengadaanDialog.open()
        }
        onCurrentItemDataChanged: {
            if (currentItemData != null) {
                pengadaanDetailFrame.pengadaanKode = currentItemData.kode
                pengadaanDetailFrame.pengadaanSumber = currentItemData.sumber
            } else {
                pengadaanDetailFrame.pengadaanKode = ""
                pengadaanDetailFrame.pengadaanSumber = ""
            }
        }
    }

    PengadaanDetailFrame {
        id: pengadaanDetailFrame
        pengadaanBukuModel: pengadaanBukuModel
        onEditClicked: {
            editPengadaanDialog.pengadaanKode = pengadaanKode
            editPengadaanDialog.pengadaanSumber = pengadaanSumber
            editablePengadaanBukuModel.populateFrom(pengadaanBukuModel);
            editPengadaanDialog.open();
        }
        onDeleteClicked: {
            pengadaanBukuModel.removeAll();
            pengadaanModel.remove(pengadaanDetailFrame.detailKode);
        }
    }

    PengadaanEditDialog {
        id: editPengadaanDialog
        pengadaanBukuModel: editablePengadaanBukuModel
        bukuModel: pengadaanBukuListModel
        onAccepted: {
            if (pengadaanKode == "") {
                pengadaanKode = pengadaanModel.add(pengadaanSumber);
                pengadaanBukuModel.addAll(pengadaanKode, editablePengadaanBukuModel);
            } else {
                pengadaanModel.update(pengadaanKode, pengadaanSumber);
                pengadaanBukuModel.updateAll(editablePengadaanBukuModel);
            }
        }
    }
}
