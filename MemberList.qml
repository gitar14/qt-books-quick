import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Item {
    Layout.fillHeight: true
    Layout.fillWidth: true

    signal addClicked()
    property var currentItemData
    property MemberModel listModel

    AppGridView {
        id: memberGridView
        model: listModel

        onCurrentItemChanged: {
             if(currentItem==null){
                 currentItemData=null

                }
             else {
                 currentItemData=currentItem.itemData

                }
        }

        delegate: CardDelegate {
            property var itemData: model
            width: GridView.view.cellWidth - 8
            height: GridView.view.cellHeight - 8
            highlighted: GridView.isCurrentItem
            onClicked: memberGridView.currentIndex = index
            padding: 16

            contentItem: ColumnLayout{
                Image {
                    source: "qrc:/icons/assignment-ind-black.svg"
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                    width: 48
                    height: 48
                    sourceSize.width: 48
                    sourceSize.height: 48
                }

                Label {
                    Layout.fillWidth: true
                    text: TextHighlighter.highlightText(model.name, listModel.textQuery)
                    horizontalAlignment: Qt.AlignHCenter
                    wrapMode: Label.Wrap
                    maximumLineCount: 2
                    elide: Text.ElideRight
                    textFormat: Label.StyledText
                }
                Label {
                    Layout.fillWidth: true
                    text: model.tanggalLahir
                    horizontalAlignment: Qt.AlignHCenter
                    wrapMode: Text.Wrap
                }
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
