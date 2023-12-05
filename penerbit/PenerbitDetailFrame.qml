import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

BaseDetailFrame {
    property PenerbitViewModel currentViewModel
    signal editClicked()
    signal deleteClicked()

    ColumnLayout {
        anchors.fill: parent
        visible: currentViewModel.hasSelectedItem

        Text {
            text: "Detail Penerbit"
            font.pixelSize: 24
        }

        Label{
            text: "Nama"
        }

        Label{
            font.bold: true
            text: currentViewModel.selectedData.nama
        }

        Label{
            text: "Alamat"
        }

        Label{
            font.bold: true
            text: currentViewModel.selectedData.alamat
        }

        Item{
            Layout.fillHeight: true
        }

        Row {
            Layout.alignment: Qt.AlignRight
            spacing: 8
            Button{
                text: "Edit"
                onClicked: editClicked()
            }
            Button{
                text: "Hapus"
                onClicked: deleteClicked()
                highlighted: true
                Material.accent: Material.Red
            }
        }
    }
    Label {
        text: "Tidak penerbit yang terpilih"
        visible: !currentViewModel.hasSelectedItem
    }
}
