import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

BaseDetailFrame {
    property KategoriViewModel currentViewModel
    signal editClicked()
    signal deleteClicked()

    ColumnLayout {
        anchors.fill: parent
        visible: currentViewModel.hasSelectedItem

        Text {
            text: "Detail Kategori"
            font.pixelSize: 24
        }

        Label {
            text: "Nama Kategori"
        }

        Label {
            font.bold: true
            text: currentViewModel.selectedData.nama
        }

        Rectangle {
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
        text: "Tidak ada kategori yang terpilih"
    }
}
