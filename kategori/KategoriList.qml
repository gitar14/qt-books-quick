import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

Item {
    Layout.fillWidth: true
    Layout.fillHeight: true

    property KategoriViewModel currentViewModel
    signal addClicked()

    AppGridView {
        id: kategoriGrid
        onCurrentIndexChanged: currentViewModel.setSelectedIndex(currentIndex)
        model: currentViewModel.list

        delegate: CardDelegate {
            width: GridView.view.cellWidth - 8
            height: GridView.view.cellHeight - 8
            highlighted: GridView.isCurrentItem
            onClicked: GridView.view.currentIndex = index
            padding: 8

            contentItem: ColumnLayout {
                Image {
                    source: "qrc:/icons/buku-black.svg"
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                    width: 48
                    height: 48
                    sourceSize.width: 48
                    sourceSize.height: 48
                }

                Label {
                    text: TextHighlighter.highlightText(modelData.nama, currentViewModel.textQuery)
                    textFormat: Label.StyledText
                    Layout.fillWidth: true
                    horizontalAlignment: Qt.AlignHCenter
                    wrapMode: Label.Wrap
                    maximumLineCount: 3
                    elide: Label.ElideRight
                }
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
