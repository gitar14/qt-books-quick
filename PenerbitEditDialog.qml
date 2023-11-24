import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Kelompok7.Perpus

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

        Label {
            text: "Nama"
        }

        TextField {
            text: viewModel.namaField.value
            maximumLength: viewModel.namaField.maxLength
            Layout.fillWidth: true
            onTextChanged: viewModel.namaField.value = text
        }

        Label {
            Layout.alignment: Qt.AlignRight
            text: viewModel.namaField.availableLength + " tersisa"
        }

        Label {
            text: viewModel.namaField.errorText
            color: Material.color(Material.Red)
            visible: !viewModel.namaField.isValid
        }

        Label {
            text : "Alamat"
        }

        TextField {
            text: viewModel.alamatField.value
            maximumLength: viewModel.alamatField.maxLength
            Layout.fillWidth: true
            onTextChanged: viewModel.alamatField.value = text;
        }

        Label {
            Layout.alignment: Qt.AlignRight
            text: viewModel.alamatField.availableLength + " tersisa"
        }

        Label {
            text: viewModel.alamatField.errorText
            color: Material.color(Material.Red)
            visible: !viewModel.alamatField.isValid
        }

    }
}
