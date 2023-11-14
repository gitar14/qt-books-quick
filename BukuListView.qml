import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ListView {
    id: bukuListView
    spacing: 8

    delegate: CardDelegate {
        property var listView: ListView.view
        property var itemData: model
        width: ListView.view.width
        height: bukuColumn.height
        padding: 16
        highlighted: ListView.isCurrentItem
        onClicked: bukuListView.currentIndex = index


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
