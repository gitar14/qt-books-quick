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

            BaseTextField {
                field: viewModel.idField
                visible: viewModel.isNew
                validator: RegularExpressionValidator {
                    regularExpression: /(?:\d|\w)*/
                }
            }

            BaseTextField {
                field: viewModel.namaDepanField
            }

            BaseTextField {
                field: viewModel.namaBelakakngField
            }

            BaseTextField {
                field: viewModel.password
                echoMode: TextInput.Password
                visible: viewModel.isNew
            }

            BaseTextField {
                field: viewModel.passwordUlang
                echoMode: TextInput.Password
                visible: viewModel.isNew
            }
        }
    }
}
