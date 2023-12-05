import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

BaseDetailFrame {
    property UserPegawaiViewModel currentViewModel
    signal editClicked()
    signal deleteClicked()

    ColumnLayout {
        anchors.fill: parent
        visible: currentViewModel.hasSelectedItem

        Label {
            text: "ID User"
        }

        Label {
            font.bold: true
            text: currentViewModel.selectedData.id
        }

        Label {
            text: "Nama Depan"
        }

        Label {
            font.bold: true
            text: currentViewModel.selectedData.namaDepan
        }

        Label {
            text: "Nama Belakang"
        }

        Label {
            font.bold: true
            text: currentViewModel.selectedData.namaBelakang
        }

        Item {
            Layout.fillHeight: true
        }

        RowLayout {
            Layout.alignment: Qt.AlignRight

            Button {
                text: "Edit"
                onClicked: editClicked()
            }

            Button {
                text: "Hapus"
                onClicked: deleteClicked()
                highlighted: true
                Material.accent: Material.Red
            }
        }
    }

    Label {
        anchors.fill: parent
        visible: !currentViewModel.hasSelectedItem

        text: "Tidak ada user yang terpilih"
    }
}
