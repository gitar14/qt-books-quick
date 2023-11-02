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
            id: penerbitGridView
            model : penerbitModel

            height: parent.height
            width: parent.width
            cellHeight: 150
            cellWidth: 125
            onCurrentItemChanged: {
                if(currentItem==null){
                    penerbitDetailFrame.penerbitKode = ""
                    penerbitDetailFrame.penerbitNama = ""
                    penerbitDetailFrame.penerbitAlamat = ""
                }
                else{
                penerbitDetailFrame.penerbitKode = currentItem.itemData.kode
                penerbitDetailFrame.penerbitNama = currentItem.itemData.name
                penerbitDetailFrame.penerbitAlamat = currentItem.itemData.alamat
                }
            }
            delegate: Rectangle {
                property var itemData: model
                width: GridView.view.cellWidth - 8
                height: GridView.view.cellHeight - 8
                border.color: "#dedede"
                border.width : 1
                radius : 16
                color: GridView.isCurrentItem ? "#efefef" : "#ffffff"

                MouseArea {
                    anchors.fill: parent

                    onClicked: penerbitGridView.currentIndex = index
                }

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

            onClicked: {
                editPenerbitDialog.penerbitKode = ""
                editPenerbitDialog.penerbitNama = ""
                editPenerbitDialog.penerbitAlamat = ""
                editPenerbitDialog.open()

            }
        }
    }

    Frame {
        id: penerbitDetailFrame
        property string penerbitKode: ""
        property string penerbitNama: ""
        property string penerbitAlamat: ""
//        border.color: "#dedede"
//        border.width: 1
//        radius: 16
        Layout.minimumWidth: 300
        width: 300
        Layout.fillHeight: true
        Layout.topMargin: 16
        Layout.bottomMargin: 16
        Layout.rightMargin: 16
        padding: 16
        GridLayout{
            anchors.fill: parent
            columns: 2
            visible: penerbitDetailFrame.penerbitKode!=""

            Label{
            text: "Kode"
            }

            Label{
            text: penerbitDetailFrame.penerbitKode
            }

            Label{
            text: "Nama"
            }

            Label{
            text: penerbitDetailFrame.penerbitNama
            }

            Label{
            text: "Alamat"
            }

            Label{
            text: penerbitDetailFrame.penerbitAlamat
            }

            Item{
            Layout.columnSpan: 2
            Layout.fillHeight: true
            }

            Row {
            Layout.columnSpan: 2
            spacing: 8
            Button{
            text: "Edit"
                onClicked: {
                editPenerbitDialog.penerbitKode = penerbitDetailFrame.penerbitKode
                editPenerbitDialog.penerbitNama = penerbitDetailFrame.penerbitNama
                editPenerbitDialog.penerbitAlamat = penerbitDetailFrame.penerbitAlamat
                editPenerbitDialog.open()
                }
            }
            Button{
                text: "Hapus"
                    onClicked: penerbitModel.remove(penerbitDetailFrame.penerbitKode)
            }
            }
        }
        Label {
            text: "Tidak Ada Data"
            visible: penerbitDetailFrame.penerbitKode==""
        }
    }

    Dialog{
        id: editPenerbitDialog
        title: penerbitKode=="" ? "Tambah Penerbit" : "Edit Penerbit"
        standardButtons: Dialog.Ok | Dialog.Cancel
        parent: Overlay.overlay
        anchors.centerIn: parent
        width: 400
        property string penerbitKode: ""
        property string penerbitNama: ""
        property string penerbitAlamat: ""

        onAccepted: {
            if(penerbitKode=="")
            penerbitModel.add(penerbitNama, penerbitAlamat)
            else penerbitModel.edit(penerbitKode,penerbitNama,penerbitAlamat)
        }

        ColumnLayout {
            anchors.fill: parent

            Label {
                text: "Nama"
            }
            TextField {
                text: editPenerbitDialog.penerbitNama
                id: namaTextField
                Layout.fillWidth: true
                onTextChanged: editPenerbitDialog.penerbitNama = text
            }
            Label {
                text : "Alamat"
            }
            TextField {
                text: editPenerbitDialog.penerbitAlamat
                id: alamatTextFiled
                Layout.fillWidth: true
                onTextChanged: editPenerbitDialog.penerbitAlamat = text
            }
        }
    }
}
