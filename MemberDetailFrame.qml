import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

BaseDetailFrame {
    property MemberViewModel currentViewModel
    signal editClicked()
    signal deleteClicked()

    GridLayout{
        anchors.fill: parent
        columns: 2
        columnSpacing: 16
        visible: currentViewModel.hasSelectedItem

        Text {
            Layout.columnSpan: 2
            text: "Member Detail"
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
        text: "Nama Depan"
        }

        Label{
             Layout.fillWidth: true
        text:  currentViewModel.selectedData.namaDepan
        }

        Label{
        text: "Nama Belakang"
        }

        Label{
             Layout.fillWidth: true
        text: currentViewModel.selectedData.namaBelakang
        }

        Label{
        text: "Tanggal Lahir"
        }

        Label{
             Layout.fillWidth: true
        text:  Qt.formatDate(currentViewModel.selectedData.tanggalLahir, locale, locale.LongFormat)
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
