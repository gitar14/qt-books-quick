import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Item {
    Layout.fillWidth: true
    Layout.fillHeight: true

    property var currentItemData
    required property PengadaanModel listModel

    signal addClicked()

    ListView {
        id: pengadaanListView
        anchors.fill: parent
        anchors.margins: 16
        model: listModel
        spacing: 8

        onCurrentItemChanged: {
            if (currentItem != null) {
                currentItemData = currentItem.itemData
            } else {
                currentItemData = null
            }
        }

        delegate: CardDelegate {
            id: pengadaanListItem
            property var itemData: model
            highlighted: ListView.isCurrentItem
            width: ListView.view.width
            onClicked: pengadaanListView.currentIndex = index
            padding: 16

            contentItem: Label {
                id: pengadaanListItemContent
                text: TextHighlighter.highlightText(model.sumber, listModel.textQueryg)
                verticalAlignment: Qt.AlignVCenter
                textFormat: Label.StyledText
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
