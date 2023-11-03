import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ListView {
    spacing: 8

    delegate: Rectangle {
        property var listView: ListView.view
        property var itemData: model
        width: ListView.view.width
        height: bukuColumn.height

        border.color: "#dedede"
        border.width: 1
        radius: 16

        color: ListView.isCurrentItem ? "#efefef" : "#ffffff"

        MouseArea {
            anchors.fill: parent
            onClicked: parent.listView.currentIndex = index
        }

        Column {
            id: bukuColumn
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
        }
    }
}
