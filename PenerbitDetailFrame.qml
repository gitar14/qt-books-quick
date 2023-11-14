import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

BaseDetailFrame {
    property string penerbitKode: ""
    property string penerbitNama: ""
    property string penerbitAlamat: ""

    signal editClicked()
    signal deleteClicked()

    GridLayout{
        anchors.fill: parent
        columns: 2
        visible: penerbitKode != ""
        columnSpacing: 16

        Text {
            Layout.columnSpan: 2
            text: "Penerbit Detail"
            font.pixelSize: 24
        }

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
