import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    Layout.fillHeight: true
    Layout.fillWidth: true

    signal addClicked()
    property var currentItemData
    property var listModel

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

            ColumnLayout{
                anchors.fill:parent
                anchors.margins: 16

                Image {
                    source: "qrc:/icons/assignment-ind-black.svg"
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                    width: 48
                    height: 48
                    sourceSize.width: 48
                    sourceSize.height: 48
                }

                Item {
                    Layout.fillHeight: true
                }

                Label {
                    text: model.name
                    Layout.alignment: Qt.AlignHCenter
                }
                Label {
                    text: model.tanggalLahir
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
    }

    FloatingActionButton {
        onClicked: addClicked()
    }
}
