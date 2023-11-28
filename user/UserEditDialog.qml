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

    property UserPegawaiEditViewModel viewModel: UserPegawaiEditViewModel {}

    title: viewModel.isNew ? "Tambah Pegawai" : "Edit Pegawai"

    onAccepted: {
        viewModel.submit()
    }

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

    contentHeight: editDialogColumn.height

    Flickable {
        id: editDialogFlickable
        anchors.fill: parent
        clip: true
        contentHeight: editDialogColumn.height

         ColumnLayout {
             id: editDialogColumn

            spacing: 8
            width: parent.width

            AppTextField {
                title: "ID"
                field: viewModel.idField
                visible: viewModel.isNew
                validator: RegularExpressionValidator {
                    regularExpression: /(?:\d|\w)*/
                }
            }

            AppTextField {
                title: "Nama Depan"
                field: viewModel.namaDepanField
            }

            AppTextField {
                title: "Nama Belakang"
                field: viewModel.namaBelakakngField
            }

            AppTextField {
                title: "Password"
                field: viewModel.password
                echoMode: TextInput.Password
                visible: viewModel.isNew
            }

            AppTextField {
                title: "Password Ulang"
                field: viewModel.passwordUlang
                echoMode: TextInput.Password
                visible: viewModel.isNew
            }
        }
    }
}
