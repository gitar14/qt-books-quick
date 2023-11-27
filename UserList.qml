import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Item {
    Layout.fillWidth: true
    Layout.fillHeight: true

    property UserPegawaiViewModel currentViewModel
    signal addClicked()

    AppGridView {
        id: userGrid
        onCurrentIndexChanged: currentViewModel.setSelectedIndex(currentIndex)
        model: currentViewModel.list
        cellHeight: 108

        delegate: CardDelegate {
            width: GridView.view.itemWidth
            height: GridView.view.itemHeight
            highlighted: GridView.isCurrentItem
            onClicked: GridView.view.currentIndex = index
            padding: 16

            contentItem: ColumnLayout {
                spacing: 2

                Image {
                    source: "qrc:/icons/user-black.svg"
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                    width: 48
                    height: 48
                    sourceSize.width: 48
                    sourceSize.height: 48
                }
                Rectangle {
                    Layout.fillHeight: true
                }

                Label {
                    text: TextHighlighter.highlightText(modelData.namaDepan + " " + modelData.namaBelakang,
                                                        currentViewModel.textQuery)
                    Layout.fillWidth: true
                    horizontalAlignment: Qt.AlignHCenter
                    textFormat: Label.StyledText
                    maximumLineCount: 2
                    elide: Label.ElideRight
                    wrapMode: Label.Wrap
                }
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}

