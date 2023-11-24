import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import Kelompok7.Perpus

Dialog {
    parent: Overlay.overlay

    width: 400
    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2

    modal: true

    property KategoriEditViewModel viewModel: KategoriEditViewModel {}

    title: viewModel.kode == -1 ? "Kategori Baru" : "Edit Kategori"

    footer: DialogButtonBox {
        Button {
            text: "Batal"
            DialogButtonBox.buttonRole: Dialog.RejectRole
            flat: true
        }
        Button {
            text: "Simpan"
            enabled: viewModel.nama.length > 0
            DialogButtonBox.buttonRole: Dialog.AcceptRole
            flat: true
        }
    }

    onAccepted: viewModel.submit()

    ColumnLayout {
        spacing: 8
        width: parent.width

        Label {
            text: "Nama"
        }

        TextField {
            Layout.fillWidth: true
            text: viewModel.nama
            onTextChanged: viewModel.nama = text
            maximumLength: viewModel.namaMaxLength
        }

        Label {
            Layout.alignment: Qt.AlignRight
            text: viewModel.namaAvailableLength + " tersisa"
        }

        Label {
            color: Material.color(Material.Red)
            text: viewModel.namaError
            visible: text.length > 0
        }
    }
}
