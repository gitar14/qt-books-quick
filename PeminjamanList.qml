import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus



Item {
    Layout.fillHeight: true
    Layout.fillWidth: true

    property var currentItemData
    required property PeminjamanModel listModel
    signal addClicked()

    ListView {
        id: peminjamanListView
        anchors.fill: parent
        anchors.margins: 16
        model: listModel
        spacing: 8

        onCurrentItemChanged: {
            if (currentItem != null){
                currentItemData = currentItem.itemData
            }
            else{
                currentItemData = null
            }
        }

        delegate: Control {
            id: peminjamanlistItem
            property var itemData: model
            property bool isSelected: ListView.isCurrentItem
            width: ListView.view.width
            padding: 16

            background: Rectangle {
                border.color: "#dedede"
                border.width: 1
                radius: 16
                color: peminjamanlistItem.isSelected ? "#efefef" : "#ffffff"

                MouseArea {
                    anchors.fill: parent

                    onClicked: peminjamanListView.currentIndex = index
                }
            }

            contentItem: Label {
                text: model.namaMember
            }
         }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }

//        height: parent.height
//        width: parent.width
//        cellHeight: 150
//        cellWidth: 125

//     Dialog {
//            id: editPeminjamDialog
//            title: "Tambah Peminjam"
//            standardButtons: Dialog.Ok | Dialog.Cancel
//            parent: Overlay.overlay
//            anchors.centerIn: parent
//            width: 400

//            onAccepted: {
//                Model.add(namaTextField.text, tgl_lahirTextFiled.text)
//            }

//            ColumnLayout {
//                anchors.fill: parent

//                Label {
//                    text: "Nama"
//                }
//                TextField {
//                    id: namaTextField
//                    Layout.fillWidth: true
//                }
//                Label {
//                    text : "Tanggal Lahir"
//                }
//                TextField {
//                    id: tgl_lahirTextFiled
//                    Layout.fillWidth: true
//                }
//            }
//    }
}
