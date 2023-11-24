import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Item {
    Layout.fillWidth: true
    Layout.fillHeight: true

    property int selectedIndex: -1
    property KategoriViewModel currentViewModel
    signal addClicked()

    AppGridView {
        id: kategoriGrid
        onCurrentIndexChanged: selectedIndex = currentIndex
        model: currentViewModel.listModel
        cellHeight: 100

        delegate: CardDelegate {
            width: GridView.view.cellWidth - 8
            height: GridView.view.cellHeight - 8
            highlighted: GridView.isCurrentItem
            onClicked: GridView.view.currentIndex = index
            padding: 16

            contentItem: ColumnLayout {
                spacing: 2

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
                    text: TextHighlighter.highlightText(model.jenis, currentViewModel.textQuery)
                    textFormat: Label.StyledText
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
