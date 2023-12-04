import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

Item {
    property PengadaanViewModel currentViewModel
    Layout.fillWidth: true
    Layout.fillHeight: true

    signal addClicked()

    ListView {
        id: pengadaanListView
        anchors.fill: parent
        anchors.margins: 16
        model: currentViewModel.list
        onCurrentIndexChanged: currentViewModel.setSelectedIndex(currentIndex)
        spacing: 8
        bottomMargin: 64 + 16

        delegate: CardDelegate {
            id: pengadaanListItem
            highlighted: ListView.isCurrentItem
            width: ListView.view.width
            onClicked: pengadaanListView.currentIndex = index
            padding: 16
            clip: true

            contentItem: ColumnLayout {
                Label {
                    text: TextHighlighter.highlightText(modelData.sumber, currentViewModel.textQuery)
                    textFormat: Label.StyledText
                    font.pixelSize: 16
                    font.bold: true
                }

                Label {
                    text: Qt.formatDate(modelData.tanggalPengadaan, locale, Locale.LongFormat)
                }
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
