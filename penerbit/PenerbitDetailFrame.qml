import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

BaseDetailFrame {
    property PenerbitViewModel currentViewModel
    signal editClicked()
    signal deleteClicked()

    GridLayout{
        anchors.fill: parent
        columns: 2
        visible: currentViewModel.hasSelectedItem
        columnSpacing: 16

        Text {
            Layout.columnSpan: 2
            text: "Penerbit Detail"
            font.pixelSize: 24
        }

        Label{
            text: "Kode"
        }

        Label{
            Layout.fillWidth: true
            text: currentViewModel.selectedData.kode
        }

        Label{
            text: "Nama"
        }

        Label{
            Layout.fillWidth: true
            text: currentViewModel.selectedData.nama
        }

        Label{
            text: "Alamat"
        }

        Label{
            Layout.fillWidth: true
            text: currentViewModel.selectedData.alamat
        }

        Item{
            Layout.columnSpan: 2
            Layout.fillHeight: true
        }

        Row {
            Layout.columnSpan: 2
            spacing: 8
            Button{
                text: "Edit"
                onClicked: editClicked()
            }
            Button{
                text: "Hapus"
                onClicked: deleteClicked()
            }
        }
    }
    Label {
        text: "Tidak Ada Data"
        visible: !currentViewModel.hasSelectedItem
    }
}
