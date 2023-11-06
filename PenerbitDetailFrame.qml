import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Frame {
//    id: penerbitDetailFrame
    property string penerbitKode: ""
    property string penerbitNama: ""
    property string penerbitAlamat: ""

    signal editClicked()
    signal deleteClicked()

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
        visible: penerbitKode != ""
        columnSpacing: 16

        Label{
            text: "Kode"
        }

        Label{
            Layout.fillWidth: true
            text: penerbitKode
        }

        Label{
            text: "Nama"
        }

        Label{
            Layout.fillWidth: true
            text: penerbitNama
        }

        Label{
            text: "Alamat"
        }

        Label{
            Layout.fillWidth: true
            text: penerbitAlamat
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
                onClicked: editClicked()
            }
            Button{
                text: "Hapus"
                onClicked: deleteClicked()
            }
        }
    }
    Label {
        text: "Tidak Ada Data"
        visible: penerbitKode == ""
    }
}
