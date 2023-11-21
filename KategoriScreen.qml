import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Kelompok7.Perpus

Page {
    leftPadding: sidebarRadius

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            Label {
                Layout.fillWidth: true
                text: "Kategori"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.pixelSize: 20
            }

            SearchField {
                text: kategoriModel.textQuery
                onTextChanged: kategoriModel.textQuery = text
            }
        }
    }


    KategoriModel {
        id: kategoriModel
    }

    RowLayout {
        anchors.fill: parent

        KategoriList {
            listModel: kategoriModel
            onAddClicked: {
                kategoriEditDialog.kategoriKode = -1
                kategoriEditDialog.kategoriJenis = ""
                kategoriEditDialog.open()
            }

            onCurrentItemDataChanged: {
                if (currentItemData == null) {
                    kategoriDetailFrame.kategoriKode = -1
                    kategoriDetailFrame.kategoriJenis = ""
                } else {
                    kategoriDetailFrame.kategoriKode = currentItemData.kode
                    kategoriDetailFrame.kategoriJenis = currentItemData.jenis
                }
            }
        }

        KategoriDetailFrame {
            id: kategoriDetailFrame
            onEditClicked: {
                kategoriEditDialog.kategoriKode = kategoriKode
                kategoriEditDialog.kategoriJenis = kategoriJenis
                kategoriEditDialog.open()
            }
            onDeleteClicked: kategoriModel.remove(kategoriKode)
        }


        KategoriEditDialog{
            id: kategoriEditDialog

            onAccepted: {
                if (kategoriKode == -1)
                    kategoriModel.addNew(kategoriJenis)
                else kategoriModel.edit(
                         kategoriKode,
                         kategoriJenis
                    )
            }
        }
    }
}
