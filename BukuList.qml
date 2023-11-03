import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    Layout.fillHeight: true
    Layout.fillWidth: true

    property var listModel
    property var currentItemData

    signal addClicked()

    ListView {
        id: listView
        anchors.fill: parent
        anchors.margins: 16
        anchors.bottomMargin: 64 + 16 + 16
        onCurrentItemChanged: {
            if (currentItem == null){
                currentItemData = null
            }
            else {
                currentItemData = currentItem.itemData
            }
        }

        spacing: 8
        model: listModel

        delegate: Rectangle {
            property var listView: ListView.view
            property var itemData: model
            width: ListView.view.width
            height: column.height

            border.color: "#dedede"
            border.width: 1
            radius: 16

            color: ListView.isCurrentItem ? "#efefef" : "#ffffff"

            MouseArea {
                anchors.fill: parent
                onClicked: parent.listView.currentIndex = index
            }

            Column {
                id: column
                width: parent.width
                padding: 16

                Text {
                    text: model.judul
                }

                Text {
                    text: model.penulis
                }

                Text {
                    text: model.kategori
                }

                Label{
                    text: model.penerbit
                }
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
