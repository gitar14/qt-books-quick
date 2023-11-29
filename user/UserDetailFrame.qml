import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

BaseDetailFrame {
    property UserPegawaiViewModel currentViewModel
    signal editClicked()
    signal deleteClicked()

    GridLayout {
        anchors.fill: parent
        columns: 2
        columnSpacing: 16
        visible: currentViewModel.hasSelectedItem

        Label {
            text: "ID User"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedData.id
        }

        Label {
            text: "Nama Depan"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedData.namaDepan
        }

        Label {
            text: "Nama Belakang"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedData.namaBelakang
        }

        Item {
            Layout.fillHeight: true
            Layout.columnSpan: 2
        }

        RowLayout {
            Layout.columnSpan: 2

            Button {
                text: "Edit"
                onClicked: editClicked()
            }

            Button {
                text: "Hapus"
                onClicked: deleteClicked()
            }
        }
    }

    Label {
        anchors.fill: parent
        visible: !currentViewModel.hasSelectedItem

        text: "Tidak ada user yang terpilih"
    }
}
