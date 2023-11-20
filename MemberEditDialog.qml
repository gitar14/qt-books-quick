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
            id: memberNamaDepanTextField
            text: editMemberDialog.memberNamaDepan
            maximumLength: 25
            Layout.fillWidth: true
            onTextChanged: editMemberDialog.memberNamaDepan = text
        }

        Label {
            Layout.alignment: Qt.AlignRight
            text: (memberNamaDepanTextField.maximumLength - memberNamaDepan.length) + " tersisa"
        }

        Label {
            text: "Nama Depan Tidak Boleh Kosong"
            color: Material.color(Material.Red)
            visible: memberNamaDepan.length == 0
        }
        Label {
            text: "Nama Belakang"
        }
        TextField {
            id: memberNamaBelakangTextField
            text: editMemberDialog.memberNamaBelakang
            maximumLength: 25
            Layout.fillWidth: true
            onTextChanged: editMemberDialog.memberNamaBelakang = text
        }

        Label {
            Layout.alignment: Qt.AlignRight
            text: (memberNamaBelakangTextField.maximumLength - memberNamaBelakang.length) + " tersisa"
        }

        Label {
            text: "Nama Belakang Tidak Boleh Kosong"
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
