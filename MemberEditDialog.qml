import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog{
    title: memberKode=="" ? "Tambah Member" : "Edit Member"
    standardButtons: Dialog.Ok | Dialog.Cancel
    parent: Overlay.overlay
    anchors.centerIn: parent
    width: 400
    property string memberKode: ""
    property string memberNamaDepan: ""
     property string memberNamaBelakang: ""
    property string memberTanggalLahir: ""



    ColumnLayout {
        anchors.fill: parent

        Label {
            text: "Nama Depan"
        }
        TextField {
            text: editMemberDialog.memberNamaDepan
            id: namaDepanTextField
            Layout.fillWidth: true
            onTextChanged: editMemberDialog.memberNamaDepan = text
        }
        Label {
            text: "Nama Belakang"
        }
        TextField {
            text: editMemberDialog.memberNamaBelakang
            id: namaBelakangTextField
            Layout.fillWidth: true
            onTextChanged: editMemberDialog.memberNamaBelakang = text
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
