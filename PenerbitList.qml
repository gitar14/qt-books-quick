import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

RowLayout {
    PenerbitModel {
        id: penerbitModel
    }

    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.leftMargin: 16
        Layout.topMargin: 16
        Layout.bottomMargin: 16
        GridView {
            model : penerbitModel

            height: parent.height
            width: parent.width
            cellHeight: 150
            cellWidth: 125
            delegate: Rectangle {
                width: GridView.view.cellWidth - 8
                height: GridView.view.cellHeight - 8
                border.color: "#dedede"
                border.width : 1
                radius : 16

                ColumnLayout{
                    anchors.fill:parent
                    anchors.margins: 16
                    Rectangle{
                        Layout.fillHeight: true

                    }
                    Label {
                        text: model.name
                        Layout.alignment: Qt.AlignHCenter
                    }
                    Label {
                        text: model.alamat
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }
        }

        RoundButton {
            text : "+"
            width : 64
            height : 64
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            font.pixelSize: 24

            onClicked: editPenerbitDialog.open()
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

    Dialog{
        id: editPenerbitDialog
        title: "Tambah Penerbit"
        standardButtons: Dialog.Ok | Dialog.Cancel
        parent: Overlay.overlay
        anchors.centerIn: parent
        width: 400

        onAccepted: {
            penerbitModel.add(namaTextField.text, alamatTextFiled.text)
        }

        ColumnLayout {
            anchors.fill: parent

            Label {
                text: "Nama"
            }
            TextField {
                id: namaTextField
                Layout.fillWidth: true
            }
            Label {
                text : "Alamat"
            }
            TextField {
                id: alamatTextFiled
                Layout.fillWidth: true
            }
        }
    }
}
