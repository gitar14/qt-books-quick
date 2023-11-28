import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Kelompok7.Perpus
import "../"

Dialog {
    property BukuEditViewModel viewModel: BukuEditViewModel {
    }

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

    onAccepted: viewModel.submit()


    parent: Overlay.overlay

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    width: 400
    contentHeight: editDialogColumn.height

    modal: true
    title: viewModel.isNew ? "Tambah Buku" : "Edit Buku"

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
                title: "Judul"
                field: viewModel.judulField
            }

            AppTextField {
                title: "Penulis"
                field: viewModel.penulisField
            }

            AppComboField {
                title: "Kategori"
                field: viewModel.kategoriField
                selectionModel: viewModel.kategoriList
                displayRole: "nama"
            }

            AppComboField {
                title: "Penerbit"
                field: viewModel.penerbitField
                selectionModel: viewModel.penerbitList
                displayRole: "nama"
            }

            AppSpinField {
                title: "Jumlah Hilang"
                visible: !viewModel.isNew
                value: viewModel.jumlahHilang
                onValueChanged: viewModel.jumlahHilang = value
                editable: true
                from: 0
                to: 10000
            }

            AppSpinField {
                title: "Tahun Terbit"
                value: viewModel.tahunTerbit
                onValueChanged: viewModel.tahunTerbit = value
                editable: true
                from: 0
                to: 10000
            }
        }
    }
}
