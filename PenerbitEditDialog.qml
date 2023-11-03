import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog{
    title: penerbitKode == "" ? "Tambah Penerbit" : "Edit Penerbit"
    standardButtons: Dialog.Ok | Dialog.Cancel
    parent: Overlay.overlay
    anchors.centerIn: parent
    width: 400

    property string penerbitKode: ""
    property string penerbitNama: ""
    property string penerbitAlamat: ""

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: "Nama"
        }
        TextField {
            text: editPenerbitDialog.penerbitNama
            Layout.fillWidth: true
            onTextChanged: editPenerbitDialog.penerbitNama = text
        }
        Label {
            text : "Alamat"
        }
        TextField {
            text: editPenerbitDialog.penerbitAlamat
            Layout.fillWidth: true
            onTextChanged: editPenerbitDialog.penerbitAlamat = text
        }
    }
}
