import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

RowLayout {
    Column {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.leftMargin: 16
        Layout.topMargin: 16
        Layout.bottomMargin: 16
        GridView {
            model : memberModel

            height: parent.height
            width: parent.width
            cellHeight: 150
            cellWidth: 125
            delegate: Rectangle {
                width: GridView.view.cellwidth - 8
                height: GridView.view.cellwidth - 8
                border.color: "#dedede"
                border.width: 1
                radius: 16

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
                        text: model.tgl_lahir
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
        id: editMemberDialog
        title: "Tambah Member"
        standardButtons: Dialog.Ok | Dialog.Cancel
        parent: Overlay.overlay
        anchors.centerIn: parent
        width: 400

        onAccepted: {
            memberModel.add(namaTextField.text, tgl_lahirTextFiled.text)
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
                text : "Tanggal Lahir"
            }
            TextField {
                id: tgl_lahirTextFiled
                Layout.fillWidth: true
            }
        }
    }
}
