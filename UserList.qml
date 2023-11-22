import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Item {
    Layout.fillWidth: true
    Layout.fillHeight: true

    property var currentItemData
    property UserModel listModel
    signal addClicked()

    AppGridView {
        id: userGrid

        onCurrentItemChanged: {
            if (currentItem == null) {
                currentItemData = null
            } else {
                currentItemData = currentItem.itemData
            }
        }

        model: listModel
        cellHeight: 108

        delegate: CardDelegate {
            property var itemData: model
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
                    text: TextHighlighter.highlightText(model.name, listModel.textQuery)
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

