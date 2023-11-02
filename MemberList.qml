import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

RowLayout {
    MemberModel{
         id : memberModel
    }

    Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.leftMargin: 16
        Layout.topMargin: 16
        Layout.bottomMargin: 16
        GridView {
            id: memberGridView
            model : memberModel

            height: parent.height
            width: parent.width
            cellHeight: 150
            cellWidth: 125
            onCurrentItemChanged: {
                 if(currentItem==null){
                    memberDetailFrame.memberKode = ""
                    memberDetailFrame.memberNama = ""
                    memberDetailFrame.memberTanggalLahir = ""
                    }
                 else{
                    memberDetailFrame.memberKode = currentItem.itemData.kode
                    memberDetailFrame.memberNama = currentItem.itemData.name
                    memberDetailFrame.memberTanggalLahir = currentItem.itemData.tanggalLahir
                    }
            }

            delegate: Rectangle {
                property var itemData: model
                width: GridView.view.cellwidth - 8
                height: GridView.view.cellwidth - 8
                border.color: "#dedede"
                border.width: 1
                radius: 16
                color: GridView.isCurrentItem ? "#efefef" : "#ffffff"

                MouseArea {
                    anchors.fill: parent

                    onClicked: memberGridView.currentIndex = index
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
                        text: model.tanggalLahir
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
                editMemberDialog.memberKode = ""
                editMemberDialog.memberNama = ""
                editMemberDialog.memberTanggalLahir = ""
                editMemberDialog.open()
            }
        }
    }

    Frame {
        id: memberDetailFrame
        property string memberKode: ""
        property string memberNama: ""
        property string memberTanggalLahir: ""

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
            visible: memberDetailFrame.memberKode!=""

            Label{
            text: "Kode"
            }

            Label{
            text:  memberDetailFrame.memberKode
            }

            Label{
            text: "Nama"
            }

            Label{
            text:  memberDetailFrame.memberNama
            }

            Label{
            text: "Tanggal Lahir"
            }

            Label{
            text:  memberDetailFrame.memberTanggalLahir
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
                editMemberDialog.memberKode = memberDetailFrame.memberKode
                editMemberDialog.memberNama = memberDetailFrame.memberNama
                editMemberDialog.memberTanggalLahir = memberDetailFrame.memberTanggalLahir
                editMemberDialog.open()
                }
            }
            Button{
                text: "Hapus"
                    onClicked: memberModel.remove(memberDetailFrame.memberKode)
            }
            }
        }
        Label {
            text: "Tidak Ada Data"
            visible: memberDetailFrame.memberKode==""
        }
    }

    Dialog{
        id: editMemberDialog
        title: memberKode=="" ? "Tambah Member" : "Edit Member"
        standardButtons: Dialog.Ok | Dialog.Cancel
        parent: Overlay.overlay
        anchors.centerIn: parent
        width: 400
        property string memberKode: ""
        property string memberNama: ""
        property string memberTanggalLahir: ""

        onAccepted:{
            if(memberKode=="")
            memberModel.add(memberNama, memberTanggalLahir)
            else memberModel.edit(memberKode,memberNama,memberTanggalLahir)
        }

        ColumnLayout {
            anchors.fill: parent

            Label {
                text: "Nama"
            }
            TextField {
                text: editMemberDialog.memberNama
                id: namaTextField
                Layout.fillWidth: true
                onTextChanged: editMemberDialog.memberNama = text
            }
            Label {
                text : "Tanggal Lahir"
            }
            TextField {
                text: editMemberDialog.memberTanggalLahir
                id: tanggalLahirTextFiled
                Layout.fillWidth: true
                onTextChanged: editMemberDialog.memberTanggalLahir = text
            }
        }
    }
}
