import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Kelompok7.Perpus
import "../"

Dialog{
    id: dialog
    title: viewModel.isNew ? "Tambah Member" : "Edit Member"
    parent: Overlay.overlay
    anchors.centerIn: parent
    width: 400
    property MemberEditViewModel viewModel: MemberEditViewModel {}

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

        AppTextField {
            title: "Nama Depan"
            field: viewModel.namaDepanField
        }

        AppTextField {
            title: "Nama Belakang"
            field: viewModel.namaBelakangField
        }

        DateField {
            title: "Tanggal Lahir"
            currentDate: viewModel.tanggalLahir
            id: tanggalLahirTextField
            onCurrentDateChanged: viewModel.tanggalLahir = currentDate
        }
    }
}
