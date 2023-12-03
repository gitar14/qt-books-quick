import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

Item {
    Layout.fillWidth: true
    Layout.fillHeight: true

    property UserPegawaiViewModel currentViewModel
    signal addClicked()

    AppGridView {
        id: userGrid
        onCurrentIndexChanged: currentViewModel.setSelectedIndex(currentIndex)
        model: currentViewModel.list

        delegate: CardDelegate {
            width: GridView.view.itemWidth
            height: GridView.view.itemHeight
            highlighted: GridView.isCurrentItem
            onClicked: GridView.view.currentIndex = index
            padding: 8

            contentItem: ColumnLayout {

                Image {
                    source: "qrc:/icons/user-black.svg"
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                    width: 48
                    height: 48
                    sourceSize.width: 48
                    sourceSize.height: 48
                }

                Label {
                    text: TextHighlighter.highlightText(modelData.nama,
                                                        currentViewModel.textQuery)
                    Layout.fillWidth: true
                    horizontalAlignment: Qt.AlignHCenter
                    textFormat: Label.StyledText
                    maximumLineCount: 3
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

