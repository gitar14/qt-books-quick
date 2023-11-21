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
            editablePengadaanBukuModel.clear();
            editPengadaanDialog.open()
        }
        onCurrentItemDataChanged: {
            if (currentItemData != null) {
                pengadaanDetailFrame.pengadaanKode = currentItemData.kode
                pengadaanDetailFrame.pengadaanSumber = currentItemData.sumber
            } else {
                pengadaanDetailFrame.pengadaanKode = -1
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
            if (pengadaanKode == -1) {
                pengadaanKode = pengadaanModel.add(pengadaanSumber);
                pengadaanBukuModel.addAll(pengadaanKode, editablePengadaanBukuModel);
            } else {
                pengadaanModel.update(pengadaanKode, pengadaanSumber);
                pengadaanBukuModel.updateAll(editablePengadaanBukuModel);
            }
        }
    }
    }
}
