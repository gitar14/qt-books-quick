import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

Dialog {
    parent: Overlay.overlay

    width: 400
    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2

    modal: true

    property KategoriEditViewModel viewModel: KategoriEditViewModel {}

    title: viewModel.isNew ? "Kategori Baru" : "Edit Kategori"

    footer: DialogButtonBox {
        Button {
            text: "Batal"
            DialogButtonBox.buttonRole: Dialog.RejectRole
            flat: true
        }
        Button {
            text: "Simpan"
            enabled: viewModel.isValid
            DialogButtonBox.buttonRole: Dialog.AcceptRole
            flat: true
        }
    }

    onAccepted: viewModel.submit()

    ColumnLayout {
        spacing: 8
        width: parent.width

        BaseTextField {
            field: viewModel.namaField
        }
    }
}
