import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

Dialog {
    parent: Overlay.overlay

    width: 400
    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2

    modal: true

    property int kategoriKode: -1
    property string kategoriJenis: ""

    title: kategoriKode == -1 ? "Kategori Baru" : "Edit Kategori"

    footer: DialogButtonBox {
        Button {
            text: "Batal"
            DialogButtonBox.buttonRole: Dialog.RejectRole
            flat: true
        }
        Button {
            text: "Simpan"
            enabled: kategoriJenis.length > 0
            DialogButtonBox.buttonRole: Dialog.AcceptRole
            flat: true
        }
    }

    ColumnLayout {
        spacing: 8
        width: parent.width

        Label {
            text: "Nama"
        }

        TextField {
            id: kategoriTextField
            Layout.fillWidth: true
            text: kategoriJenis
            onTextChanged: kategoriJenis = text
            maximumLength: 25
        }

        Label {
            Layout.alignment: Qt.AlignRight
            text: (kategoriTextField.maximumLength - kategoriJenis.length) + " tersisa"
        }

        Label {
            color: Material.color(Material.Red)
            text: "Nama tidak boleh kosong"
            visible: kategoriJenis.length == 0
        }
    }
}
