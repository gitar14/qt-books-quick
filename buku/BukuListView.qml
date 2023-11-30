import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

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
                text: modelData.namaKategori
                font.pixelSize: 12
            }

            Text {
                text: TextHighlighter.highlightText(modelData.judul, highlightedText)
                textFormat: Text.StyledText
                font.pixelSize: 16
                font.bold: true
            }

            Text {
                text: modelData.penulis
                font.pixelSize: 14
            }
        }
    }
}
