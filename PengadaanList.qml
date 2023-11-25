import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

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

        delegate: CardDelegate {
            id: pengadaanListItem
            highlighted: ListView.isCurrentItem
            width: ListView.view.width
            onClicked: pengadaanListView.currentIndex = index
            padding: 16

            contentItem: Label {
                id: pengadaanListItemContent
                text: TextHighlighter.highlightText(modelData.sumber, currentViewModel.textQuery)
                verticalAlignment: Qt.AlignVCenter
                textFormat: Label.StyledText
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
