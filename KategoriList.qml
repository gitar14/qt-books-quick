import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true

    property var currentItemData
    property var listModel
    signal addClicked()

    Column {
        anchors.fill: parent
        padding: 16

        GridView {
            id: kategoriGrid
            width: Math.min(count, Math.floor((parent.width - parent.leftPadding - parent.rightPadding) / cellWidth)) * cellWidth
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height
            cellWidth: 125
            cellHeight: 150

            onCurrentItemChanged: {
                if (currentItem == null) {
                    currentItemData = null
                } else {
                    currentItemData = currentItem.itemData
                }
            }

            model: listModel

            delegate: CardDelegate {
                property var itemData: model
                width: GridView.view.cellWidth - 8
                height: GridView.view.cellHeight - 8
                highlighted: GridView.isCurrentItem
                onClicked: GridView.view.currentIndex = index

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 2

                    Rectangle {
                        Layout.fillHeight: true
                    }

                    Label {
                        text: model.jenis
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
