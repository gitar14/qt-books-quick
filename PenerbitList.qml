import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Item  {
    Layout.fillHeight: true
    Layout.fillWidth: true

    signal addClicked()
    property PenerbitModel listModel
    property var currentItemData

    AppGridView {
        id: penerbitGridView
        model : listModel

        onCurrentItemChanged: {
            if(currentItem == null){
                currentItemData = null;
            }
            else{
                currentItemData = currentItem.itemData;
            }
        }
        cellHeight: 125

        delegate: CardDelegate {
            property var itemData: model
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
                    text: TextHighlighter.highlightText(model.name, listModel.textQuery)
                    Layout.alignment: Qt.AlignHCenter
                    textFormat: Label.StyledText
                }
                Label {
                    text: model.alamat
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
