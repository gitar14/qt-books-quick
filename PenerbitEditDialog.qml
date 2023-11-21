import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Dialog{
    title: penerbitKode == -1 ? "Tambah Penerbit" : "Edit Penerbit"
    parent: Overlay.overlay
    anchors.centerIn: parent
    width: 400

    property int penerbitKode: -1
    property string penerbitNama: ""
    property string penerbitAlamat: ""

    footer : DialogButtonBox {
        Button {
            text: "Batal"
            DialogButtonBox.buttonRole: Dialog.RejectRole
            flat: true
        }
        Button {
            text: "Simpan"
            enabled: penerbitNama.length > 0 && penerbitAlamat.length > 0
            DialogButtonBox.buttonRole: Dialog.AcceptRole
            flat: true
        }
    }
    ColumnLayout {
        anchors.fill: parent

        Label {
            text: "Nama"
        }
        TextField {
            id: penerbitNamaTextField
            text: editPenerbitDialog.penerbitNama
            maximumLength: 25
            Layout.fillWidth: true
            onTextChanged: editPenerbitDialog.penerbitNama = text
        }

        Label {
            Layout.alignment: Qt.AlignRight
            text: (penerbitNamaTextField.maximumLength - penerbitNama.length) + " tersisa"
        }

        Label {
            text: "Nama Tidak Boleh Kosong"
            color: Material.color(Material.Red)
            visible: penerbitNama.length == 0
        }

        Label {
            text : "Alamat"
        }

        TextField {
            id: penerbitAlamatTextField
            text: editPenerbitDialog.penerbitAlamat
            maximumLength: 30
            Layout.fillWidth: true
            onTextChanged: editPenerbitDialog.penerbitAlamat = text
        }

        Label {
            Layout.alignment: Qt.AlignRight
            text: (penerbitAlamatTextField.maximumLength - penerbitAlamat.length) + " tersisa"
        }

        Label {
            text: "Alamat Tidak Boleh Kosong"
            color: Material.color(Material.Red)
            visible: penerbitAlamat.length == 0
        }

    }
}
