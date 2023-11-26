import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Kelompok7.Perpus

Dialog{
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

        BaseTextField {
            field: viewModel.namaDepanField
        }

        BaseTextField {
            field: viewModel.namaBelakangField
        }

        Label {
            text : "Tanggal Lahir"
        }
        DateField {
            currentDate: viewModel.tanggalLahir
            id: tanggalLahirTextField
            Layout.fillWidth: true
            onCurrentDateChanged: viewModel.tanggalLahir = currentDate
        }
    }
}
