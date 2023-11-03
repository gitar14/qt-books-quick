import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Frame {
    property string memberKode: ""
    property string memberNamaDepan: ""
    property string memberNamaBelakang: ""
    property string memberTanggalLahir: ""

    signal editClicked()
    signal deleteClicked()

    Layout.minimumWidth: 300
    Layout.maximumWidth: 300
    Layout.fillHeight: true
    Layout.topMargin: 16
    Layout.bottomMargin: 16
    Layout.rightMargin: 16
    padding: 16
    GridLayout{
        anchors.fill: parent
        columns: 2
        visible: memberKode!=""

        Label{
        text: "Kode"
        }

        Label{
            Layout.fillWidth: true
        text: memberKode
        }

        Label{
        text: "Nama Depan"
        }

        Label{
             Layout.fillWidth: true
        text:  memberNamaDepan
        }

        Label{
        text: "Nama Belakang"
        }

        Label{
             Layout.fillWidth: true
        text: memberNamaBelakang
        }

        Label{
        text: "Tanggal Lahir"
        }

        Label{
             Layout.fillWidth: true
        text:  memberTanggalLahir
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
        visible: memberDetailFrame.memberKode==""
    }
}
