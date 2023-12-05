import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

BaseDetailFrame {
    property MemberViewModel currentViewModel
    signal editClicked()
    signal deleteClicked()

    ColumnLayout {
        anchors.fill: parent
        visible: currentViewModel.hasSelectedItem

        Text {
            text: "Detail Member"
            font.pixelSize: 24
        }

        Label{
            text: "Nama Depan"
        }

        Label{
            font.bold: true
            text:  currentViewModel.selectedData.namaDepan
        }

        Label{
            text: "Nama Belakang"
        }

        Label{
            font.bold: true
            text: currentViewModel.selectedData.namaBelakang
        }

        Label{
            text: "Tanggal Lahir"
        }

        Label{
            font.bold: true
            text:  Qt.formatDate(currentViewModel.selectedData.tanggalLahir, locale, Locale.LongFormat)
        }

        Label {
            text: "Umur"
        }

        Label {
            font.bold: true
            text: currentViewModel.selectedData.umur + " tahun"
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
        text: "Tidak member yang terpilih"
        visible: !currentViewModel.hasSelectedItem
    }
}
