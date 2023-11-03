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

            delegate: Rectangle {
                property var itemData: model
                width: GridView.view.cellWidth - 8
                height: GridView.view.cellHeight - 8

                border.color: "#dedede"
                border.width: 1
                radius: 16
                color: GridView.isCurrentItem ? "#efefef" : "#ffffff"

                MouseArea {
                    anchors.fill: parent
                    onClicked: kategoriGrid.currentIndex = index
                }

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
