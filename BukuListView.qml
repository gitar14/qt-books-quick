import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

ListView {
    property string highlightedText: ""
    id: bukuListView
    spacing: 8

    delegate: CardDelegate {
        property var listView: ListView.view
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
                text: TextHighlighter.highlightText(modelData.judul, highlightedText)
                textFormat: Text.StyledText
            }

            Text {
                text: modelData.penulis
            }

            Text {
                text: modelData.namaKategori
            }
        }
    }
}
