import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus


Page {
    leftPadding: sidebarRadius
    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            Label {
                Layout.fillWidth: true
                text: "Pengadaan"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.pixelSize: 20
            }

            SearchField {
                text: pengadaanModel.textQuery
                onTextChanged: pengadaanModel.textQuery = text
            }
        }
    }
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

    RowLayout{
        anchors.fill: parent

    PengadaanList {
        listModel: pengadaanModel
        onAddClicked: {
            editPengadaanDialog.pengadaanKode = -1
            editPengadaanDialog.pengadaanSumber = ""
            editPengadaanDialog.pengadaanTanggal = new Date ()
            editablePengadaanBukuModel.clear();
            editPengadaanDialog.open()
        }
        onCurrentItemDataChanged: {
            if (currentItemData != null) {
                pengadaanDetailFrame.pengadaanKode = currentItemData.kode
                pengadaanDetailFrame.pengadaanSumber = currentItemData.sumber
                PengadaanDetailFrame.pengadaanTanggal = currentItemData.tanggal
            } else {
                pengadaanDetailFrame.pengadaanKode = -1
                pengadaanDetailFrame.pengadaanSumber = ""
                PengadaanDetailFrame.pengadaanTanggal = new Date ()
            }
        }
    }

    PengadaanDetailFrame {
        id: pengadaanDetailFrame
        pengadaanBukuModel: pengadaanBukuModel
        onEditClicked: {
            editPengadaanDialog.pengadaanKode = pengadaanKode
            editPengadaanDialog.pengadaanSumber = pengadaanSumber
            editPengadaanDialog.pengadaanTanggal = pengadaanTanggal
            editablePengadaanBukuModel.populateFrom(pengadaanBukuModel);
            editPengadaanDialog.open();
        }
        onDeleteClicked: {
            pengadaanBukuModel.removeAll();
            pengadaanModel.remove(pengadaanDetailFrame.pengadaanKode);
        }
    }

    PengadaanEditDialog {
        id: editPengadaanDialog
        pengadaanBukuModel: editablePengadaanBukuModel
        bukuModel: pengadaanBukuListModel
        onAccepted: {
            if (pengadaanKode == -1) {
                pengadaanKode = pengadaanModel.add(pengadaanSumber, pengadaanTanggal);
                pengadaanBukuModel.addAll(pengadaanKode, editablePengadaanBukuModel);
            } else {
                pengadaanModel.update(pengadaanKode, pengadaanSumber, pengadaanTanggal);
                pengadaanBukuModel.updateAll(editablePengadaanBukuModel);
            }
        }
    }
    }
}
