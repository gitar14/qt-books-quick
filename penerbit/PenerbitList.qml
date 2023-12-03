import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

Item  {
    Layout.fillHeight: true
    Layout.fillWidth: true

    signal addClicked()
    property PenerbitViewModel currentViewModel
    property var currentItemData

    AppGridView {
        id: penerbitGridView
        model: currentViewModel.list

        onCurrentIndexChanged: currentViewModel.setSelectedIndex(currentIndex)
        cellHeight: 125

        delegate: CardDelegate {
            width: GridView.view.cellWidth - 8
            height: GridView.view.cellHeight - 8
            padding: 16
            highlighted: GridView.isCurrentItem
            onClicked: penerbitGridView.currentIndex = index


            contentItem: ColumnLayout{
                Image {
                    source: "qrc:/icons/icons/homework-black.svg"
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                    width: 48
                    height: 48
                    sourceSize.width: 48
                    sourceSize.height: 48
                }

                Label {
                    Layout.fillWidth: true
                    text: TextHighlighter.highlightText(modelData.nama, currentViewModel.textQuery)
                    horizontalAlignment: Qt.AlignHCenter
                    textFormat: Label.StyledText
                    wrapMode: Label.Wrap
                }
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
