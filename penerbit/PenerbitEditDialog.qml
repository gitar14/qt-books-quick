import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Kelompok7.Perpus
import "../"

Dialog {
    property PenerbitEditViewModel viewModel: PenerbitEditViewModel {}

    title: viewModel.isNew ? "Tambah Penerbit" : "Edit Penerbit"
    parent: Overlay.overlay
    anchors.centerIn: parent
    width: 400

    onAccepted: viewModel.submit()

    footer : DialogButtonBox {
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
    ColumnLayout {
        anchors.fill: parent

        BaseTextField {
            field: viewModel.namaField
        }

        BaseTextField {
            field: viewModel.alamatField
        }
    }
}
