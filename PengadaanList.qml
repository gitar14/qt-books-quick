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

        delegate: Control {
            id: pengadaanListItem
            property var itemData: model
            property bool isSelected: ListView.isCurrentItem
            width: ListView.view.width
            padding: 16

            background: Rectangle {
                border.color: "#dedede"
                border.width: 1
                radius: 16
                color: pengadaanListItem.isSelected ? "#efefef" : "#ffffff"

                MouseArea {
                    anchors.fill: parent

                    onClicked: pengadaanListView.currentIndex = index
                }
            }

            contentItem: Label {
                id: pengadaanListItemContent
                text: model.sumber
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
