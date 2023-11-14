import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Dialog{
    title: memberKode=="" ? "Tambah Member" : "Edit Member"
    parent: Overlay.overlay
    anchors.centerIn: parent
    width: 400
    property string memberKode: ""
    property string memberNamaDepan: ""
    property string memberNamaBelakang: ""
    property date memberTanggalLahir: new Date()

    footer : DialogButtonBox {
        Button {
            text: "Batal"
            DialogButtonBox.buttonRole: Dialog.RejectRole
            flat: true
        }
        Button {
            text: "Simpan"
            enabled: memberNamaDepan.length > 0 && memberNamaBelakang.length > 0
            DialogButtonBox.buttonRole: Dialog.AcceptRole
            flat: true
        }
    }

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: "Nama Depan"
        }
        TextField {
            text: editMemberDialog.memberNamaDepan
            maximumLength: 25
            id: namaDepanTextField
            Layout.fillWidth: true
            onTextChanged: editMemberDialog.memberNamaDepan = text
        }
        Label {
            text: "Nama Tidak Boleh Kosong"
            color: Material.color(Material.Red)
            visible: memberNamaDepan.length == 0
        }
        Label {
            text: "Nama Belakang"
        }
        TextField {
            text: editMemberDialog.memberNamaBelakang
            maximumLength: 25
            id: namaBelakangTextField
            Layout.fillWidth: true
            onTextChanged: editMemberDialog.memberNamaBelakang = text
        }
        Label {
            text: "Nama Tidak Boleh Kosong"
            color: Material.color(Material.Red)
            visible: memberNamaBelakang.length == 0
        }
        Label {
            text : "Tanggal Lahir"
        }
        DateField {
            currentDate: editMemberDialog.memberTanggalLahir
            id: tanggalLahirTextField
            Layout.fillWidth: true
            onCurrentDateChanged: editMemberDialog.memberTanggalLahir = currentDate
        }
    }
}
