import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


RowLayout {
    Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.leftMargin: 16
        Layout.topMargin: 16
        Layout.bottomMargin: 16
        GridView {
            model: ListModel {
                ListElement {
                    peminjam: "Dadi"
                    tanggalMulai: "fgfg"
                    tanggalTenggat: "jjj"
                }
            }

            height: parent.height
            width: parent.width
            cellHeight: 150
            cellWidth: 125
            delegate: Rectangle {
            height: GridView.view.cellwidth - 8
            width: GridView.view.cellwidth - 8
            border.color: "#dedede"
            border.width:1
            radius: 16

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                Rectangle {
                    Layout.fillHeight: true
                    }
                Label {
                    text: model.peminjam
                    Layout.alignment: Qt.AlignHCenter
                    }
                Label {
                    text: model.tanggalMulai
                    Layout.alignment: Qt.AlignHCenter
                    }
                Label {
                    text: model.tanggalTenggat
                    Layout.alignment: Qt.AlignHCenter
                    }
                }

            }
        }
        RoundButton{
            text: "+"
            width: 64
            height: 64
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            font.pixelSize: 24
        }
    }
    Rectangle {
        border.color: "#dedede"
        border.width: 1
        radius: 16
        Layout.minimumWidth: 300
        width: 300
        Layout.fillHeight: true
        Layout.topMargin: 16
        Layout.bottomMargin: 16
        Layout.rightMargin: 16
    }
//    Dialog {
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
