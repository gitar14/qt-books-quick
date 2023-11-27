import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

BaseDetailFrame {
    property KategoriViewModel currentViewModel
    signal editClicked()
    signal deleteClicked()

    GridLayout {
        anchors.fill: parent
        columns: 2
        columnSpacing: 16
        visible: currentViewModel.hasSelectedItem

        Text {
            Layout.columnSpan: 2
            text: "Kategori Detail"
            font.pixelSize: 24
        }

        Label {
            text: "Kode"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedData.kode
        }

        Label {
            text: "Jenis"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedData.nama
        }

        Rectangle {
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
        text: "Tidak ada kategori yang terpilih"
    }
}
